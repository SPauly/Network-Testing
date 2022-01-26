#include <iostream>
#include <cstddef>
#include <cstdlib>

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif
#define ASIO_STANDALONE
#include <asio.hpp>

using asio::ip::tcp;


int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cout << "Usage: " << argv[0] << " <IP-address> <port>" << std::endl;
		return 1;
	}

	asio::io_service ioService;
	unsigned short port = atoi(argv[2]);

	tcp::endpoint server(asio::ip::address::from_string(argv[1]), port);
	tcp::socket socket(ioService);
	socket.connect(server);

	std::cout << "Local Endpoint" << socket.local_endpoint();
	std::cout << "\nConnected to " << socket.remote_endpoint() << std::endl;

	constexpr size_t SZ = 80;

	char buf[SZ + 1];

	size_t bytes = socket.read_some(asio::buffer(buf, SZ));
	buf[bytes] = '\0';
	std::cout << buf << std::endl;

	return 0;
}