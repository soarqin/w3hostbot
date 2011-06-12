#include "config.h"
#include "TcpClient.h"
#include "TcpServer.h"
#include "libevent/event.h"

namespace Network
{
	void TcpClient::_client_read_cb( int fd, short events, void * arg )
	{
		TcpClient * client = (TcpClient *)arg;
		client->_DoRecv();
	}
	void TcpClient::_client_write_cb( int fd, short events, void * arg )
	{
		TcpClient * client = (TcpClient *)arg;
		client->_DoSend();
	}

	TcpClient::TcpClient( int fd ): _fd(fd), _base(0), _r_event(0), _w_event(0), _pend_close(false), _host(0)
	{
	}

	TcpClient::~TcpClient()
	{
		if(_r_event != NULL)
		{
			delete (struct event *)_r_event;
			_r_event = NULL;
		}
		if(_w_event != NULL)
		{
			delete (struct event *)_w_event;
			_w_event = NULL;
		}
		Close();
		closesocket(_fd);
	}

	void TcpClient::Send( const byte * data, size_t len )
	{
		if(_sendbuf.empty())
		{
			struct event * ev = (struct event *)_w_event;
			event_add(ev, NULL);
		}
		_sendbuf.insert(_sendbuf.end(), data, data + len);
	}

	void TcpClient::Close()
	{
		if(_fd != 0)
		{
			shutdown(_fd, SD_BOTH);
			_fd = 0;
		}
	}

	void TcpClient::_DoRecv()
	{
		char buf[2048];
		int len = recv(_fd, buf, 2048, 0);
		if(len == 0)
		{
			if(_host != NULL)
				_host->Close(_fd);
			return;
		}
		if(len < 0)
		{
			int lerror = WSAGetLastError();
			switch(lerror)
			{
			case WSA_NOT_ENOUGH_MEMORY:
			case WSATRY_AGAIN:
			case WSAEINTR:
			case WSAEWOULDBLOCK:
			case WSAEFAULT:
				break;
			default:
				Close();
				return;
			}
		}

		OnRecv((byte *)buf, (size_t)len);
		event_add((struct event *)_r_event, NULL);
	}

	void TcpClient::_DoSend()
	{
		if(!_sendbuf.empty())
		{
			int len = send(_fd, (const char *)&_sendbuf[0], _sendbuf.size(), 0);
			if(len < 0)
			{
				int lerror = WSAGetLastError();
				switch(lerror)
				{
				case WSA_NOT_ENOUGH_MEMORY:
				case WSATRY_AGAIN:
				case WSAEINTR:
				case WSAEWOULDBLOCK:
				case WSAEFAULT:
					break;
				default:
					Close();
					return;
				}
			}
			else if(len > 0)
			{
				if(_sendbuf.size() <= (size_t)len)
					_sendbuf.clear();
				else
					_sendbuf.erase(_sendbuf.begin(), _sendbuf.begin() + len);
			}
		}
		if(_sendbuf.empty())
		{
			if(_pend_close)
			{
				_pend_close = false;
				Close();
			}
		}
		else
		{
			event_add((struct event *)_w_event, NULL);
		}
	}

	void TcpClient::_Register( TcpServer * svr )
	{
		_base = svr->_base;
		_host = svr;

		struct event * ev = new struct event;
		_r_event = (void *)ev;

		event_set(ev, _fd, EV_READ, _client_read_cb, this);
		event_base_set(_base, ev);
		event_add(ev, NULL);

		ev = new struct event;
		_w_event = (void *)ev;

		event_set(ev, _fd, EV_WRITE, _client_write_cb, this);
		event_base_set(_base, ev);
	}

	void TcpClient::PendClose()
	{
		if(_sendbuf.empty())
		{
			Close();
			return;
		}
		_pend_close = true;
	}
}
