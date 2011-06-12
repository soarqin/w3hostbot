#include "config.h"
#include "TcpServer.h"
#include "libevent/event.h"

#include <winsock2.h>
#include <windows.h>

namespace Network
{
	class TcpWorkerThread:
		public Common::Thread
	{
	public:
		virtual uint Proc(void * param)
		{
			TcpServer * ts = (TcpServer *)param;
			return ts->Worker();
		}
	};

	void TcpServer::_listen_cb( int fd, short events, void * arg )
	{
		if(events & EV_READ)
		{
			TcpServer * server = (TcpServer *)arg;
			server->Accept();
		}
		else if(events & EV_WRITE)
		{
			TcpServer * server = (TcpServer *)arg;
			event_base_loopbreak(server->_base);
		}
	}

	void TcpServer::_timer_cb( int fd, short events, void * arg )
	{
		TcpServer::ITimer * timer = (TcpServer::ITimer *)arg;
		if(timer != NULL)
		{
			if(!(*timer)())
			{
				delete timer->_event;
			}
			else
			{
				evtimer_add(timer->_event, &timer->_tv);
			}
		}
	}

	TcpServer::TcpServer(): _base(NULL), _fd_listen(0)
	{
	}

	TcpServer::~TcpServer()
	{
		Destroy();
	}

	bool TcpServer::Init( ushort port )
	{
		_base = event_base_new();
		if(_base == NULL)
			return false;

		_fd_map.clear();

		_fd_listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if(_fd_listen == -1)
		{
			Destroy();
			return false;
		}

		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons( port );
		addr.sin_addr.s_addr = INADDR_ANY;
		if(SOCKET_ERROR == ::bind( _fd_listen, (sockaddr *)&addr, sizeof( addr )) || SOCKET_ERROR == listen( _fd_listen, 20 ))
		{
			Destroy();
			return false;
		}

		static struct event _listen_event;
		event_set(&_listen_event, _fd_listen, EV_READ | EV_WRITE | EV_PERSIST, _listen_cb, this);
		event_base_set(_base, &_listen_event);
		event_add(&_listen_event, NULL);

		return true;
	}

	void TcpServer::Destroy()
	{
		if(_fd_listen != 0)
		{
			shutdown(_fd_listen, SD_BOTH);
			closesocket(_fd_listen);
			_fd_listen = 0;
		}
		if(_worker.get() != NULL)
		{
			event_base_loopbreak(_base);
			_worker->Wait();
			_worker.reset();
		}
		if(_base != NULL)
		{
			event_base_free(_base);
			_base = NULL;
		}
	}

	void TcpServer::Accept()
	{
		sockaddr_in addr;
		int size = sizeof(sockaddr_in);
		int new_fd = accept(_fd_listen, (sockaddr *)&addr, &size);
		if(new_fd == -1)
			return;
		TcpClient::Pointer cl(OnNewClient(new_fd));
		cl->_Register(this);
		_fd_map[new_fd] = cl;
	}

	uint TcpServer::Worker()
	{
		event_base_loop(_base, 0);
		return 0;
	}

	TcpClient * TcpServer::OnNewClient( int fd )
	{
		return new TcpClient(fd);
	}

	TcpClient::Pointer TcpServer::GetClient(int fd)
	{
		std::map<int, TcpClient::Pointer>::iterator it = _fd_map.find(fd);
		if(it != _fd_map.end())
			return TcpClient::Pointer();
		return it->second;
	}

	void TcpServer::Close( int fd )
	{
		_fd_map.erase(fd);
	}

	void TcpServer::RegisterTimer( uint tm, TcpServer::ITimer * timer )
	{
		timer->_event = new struct event;
		evtimer_set(timer->_event, _timer_cb, timer);
		event_base_set(_base, timer->_event);
		timer->_tv.tv_sec = tm / 1000;
		timer->_tv.tv_usec = (tm % 1000) * 1000;
		evtimer_add(timer->_event, &timer->_tv);
	}

	void TcpServer::Run()
	{
		_worker = Common::Thread::Pointer(new TcpWorkerThread());
		_worker->Start((void *)this);
	}
}
