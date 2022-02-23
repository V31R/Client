#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "Client");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Yellow);

    sf::UdpSocket socket;

    // bind the socket to a port
    if (socket.bind(54000) != sf::Socket::Done)
    {
        // error...
        shape.setFillColor(sf::Color::Red);
    }

    char data[100] = "Hellow World!";

    // UDP socket:
    sf::IpAddress recipient = "172.22.111.11";
    unsigned short port = 9993;
    if (socket.send(data, 100, recipient, port) != sf::Socket::Done)
    {
        shape.setFillColor(sf::Color::Red);
    }
    else {

        shape.setFillColor(sf::Color::Green);

    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}