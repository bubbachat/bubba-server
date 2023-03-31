namespace services
{
class ClientSocket
{
public:
    ClientSocket();
    ~ClientSocket();

private:
    int client_fd;
};
} // namespace services
