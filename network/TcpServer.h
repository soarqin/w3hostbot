#ifndef _TCPSERVER_H_
#define _TCPSERVER_H_

#include "common/Thread.h"
#include "TcpClient.h"

struct event_base;
struct event;

namespace Network
{
	class TcpServer
	{
		friend class TcpWorkerThread;
		friend class TcpClient;
	public:
		class ITimer
		{
			friend class TcpServer;
		public:
			virtual bool operator()() = 0;
		private:
			struct event * _event;
			struct timeval _tv;
		};
	public:
		TcpServer();
		virtual ~TcpServer();
		bool Init(ushort port);
		void Run();
		void Destroy();
		TcpClient::Pointer GetClient(int);
		void RegisterTimer(uint, TcpServer::ITimer *);
	protected:
		virtual TcpClient * OnNewClient(int);
		virtual void OnDisconnect(int){}
	private:
		struct event_base * _base;
		int _fd_listen;
		Common::Thread::Pointer _worker;
		std::map<int, TcpClient::Pointer> _fd_map;

		void Accept();
		uint Worker();
		void Close(int);
		static void _listen_cb( int, short, void * );
		static void _timer_cb( int, short, void * );
	};
}

#endif // _TCPSERVER_H_
