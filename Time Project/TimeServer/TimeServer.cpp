#include <ctime>
#include <iostream>
#include <cstring>
#include <cstdlib>

#pragma warning(disable : 4996)//needed to use ctime instead of ctime_s
#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif
#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>

using asio::ip::tcp;

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " <port>" << std::endl;
		return 1;
	}
	
	asio::io_service ioService;
	unsigned short port = atoi(argv[1]);

	tcp::acceptor acceptor(ioService, tcp::endpoint(tcp::v4(), port));

	while (true) {
		tcp::socket socket(ioService);

		std::cout << "listening at port " << port << " ... (Exit with ctrl+c)" << std::endl;

		acceptor.accept(socket);
		std::cout << "Local Endpoint" << socket.local_endpoint();
		std::cout << "\nConnected to " << socket.remote_endpoint() << std::endl;

		time_t now = time(NULL);
		const char* s_time = ctime(&now);

		socket.write_some(asio::buffer(s_time, strlen(s_time + 1)));

	}

	return 0;
}