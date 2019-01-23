#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

int main(int argc, char *argv[])
{
	sf::VideoMode screen(sf::VideoMode::getDesktopMode());

	sf::RenderWindow window(screen, "");
	window.setFramerateLimit(30);

	sf::Texture texture;
	if (!texture.loadFromFile("image.png"))
		return EXIT_FAILURE;

	sf::Sprite image(texture);
	image.setPosition(screen.width / 2.0f, screen.height / 2.0f);
	image.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);

	sf::Font font;
	if (!font.loadFromFile("sansation.ttf"))
		return EXIT_FAILURE;

	sf::Text text("Tap anywhere to move the logo.", font, 64);
	text.setFillColor(sf::Color::Black);
	text.setPosition(10, 10);

	sf::Music music;
	if (!music.openFromFile("orchestral.ogg"))
		return EXIT_FAILURE;
	music.play();

	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("ding.flac"))
		return EXIT_FAILURE;
	sf::Sound sound;
	sound.setBuffer(buffer);

	sf::View view = window.getDefaultView();

	sf::Color background = sf::Color::White;

	bool active = true;
	while (window.isOpen())
	{
		sf::Event event;

		while (active ? window.pollEvent(event) : window.waitEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				break;
			case sf::Event::Resized:
				view.setSize((float)event.size.width, (float)event.size.height);
				view.setCenter(event.size.width / 2.0f, event.size.height / 2.0f);
				window.setView(view);
				break;
			case sf::Event::LostFocus:
				background = sf::Color::Black;
				break;
			case sf::Event::GainedFocus:
				background = sf::Color::White;
				break;

			case sf::Event::MouseLeft:
				active = false;
				break;
			case sf::Event::MouseEntered:
				active = true;
				break;
			case sf::Event::TouchBegan:
				if (event.touch.finger == 0)
				{
					image.setPosition((float)event.touch.x, (float)event.touch.y);
					sound.play();
				}
				break;
			}
		}

		static bool down = false;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (down == false)
				sound.play();
			down = true;
		} else {
			down = false;
		}

		if (active)
		{
			window.clear(background);
			window.draw(image);
			window.draw(text);
			window.display();
		}
		else 
		{
			sf::sleep(sf::milliseconds(100));
		}
	}
}
