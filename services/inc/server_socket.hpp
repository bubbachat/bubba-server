
namespace services
{
class ServerSocket
{
public:
    ServerSocket();
    ~ServerSocket();

private:
    int server_fd;
    int client_connection_fd;
};
}
