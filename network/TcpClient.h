#ifndef _TCPCLIENT_H_
#define _TCPCLIENT_H_

#include "common/SharedPtr.h"

struct event_base;

namespace Network
{
    class TcpServer;
	class TcpClient:
		public Common::SharedClass<TcpClient>
	{
		friend class TcpServer;
	public:
		TcpClient(int fd);
		virtual ~TcpClient();
		void Send(const byte * data, size_t len);
		void Close();
		void PendClose();
		operator int() {return _fd;}
	protected:
		virtual void OnRecv(byte * data, size_t len) {}
	private:
		int _fd;
		struct event_base * _base;
		void * _r_event, * _w_event;
		bool _pend_close;
		TcpServer * _host;
		std::vector<byte> _sendbuf;

		void _DoRecv();
		void _DoSend();
		void _Register(TcpServer *);
		static void _client_write_cb(int, short, void *);
		static void _client_read_cb(int, short, void *);
	};
}

#endif // _TCPCLIENT_H_
