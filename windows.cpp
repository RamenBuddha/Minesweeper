//
// Created by shaoy on 4/12/2023.
//
#include "windows.h"

pair<bool, string> welcomeWindow() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper", sf::Style::Close);
    bool gameStart = false;

    sf::Text title;
    sf::Text prompt;
    sf::Text input;

    sf::Font WELCOMEFONTS;
    WELCOMEFONTS.loadFromFile("files/font.ttf");

    setEverything(title, WELCOMEFONTS, "UB", "white", 24);
    setEverything(prompt, WELCOMEFONTS, "B", "white", 20);
    setEverything(input, WELCOMEFONTS, "B", "yellow", 18);
    title.setString("WELCOME TO MINESWEEPER!");
    prompt.setString("Enter your name:");

    setText(title, window.getSize().x/2.0f, window.getSize().y/2.0f - 150.0f);
    setText(prompt, window.getSize().x/2.0f, window.getSize().y/2.0f - 75.0f);
    setText(input, window.getSize().x/2.0f, window.getSize().y/2.0f - 45.0f);

    sf::String name;
    string finName;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if (event.type == sf::Event::TextEntered) {
                if (!(name.getSize() > 9)) {
                    if ((event.text.unicode > 64 and event.text.unicode < 91) or
                        (event.text.unicode > 96 and event.text.unicode < 123)) {
                        name += event.text.unicode;
                    } else if (event.text.unicode == 8) {
                        name = name.substring(0, name.getSize() - 1);
                    } else if (event.text.unicode == 13 and name.getSize () != 0) {
                        finName += toupper(name[0]);
                        for (int i = 1; i < name.getSize(); i++) {
                            finName += tolower(name[i]);
                        }
                        gameStart = true;
                        window.close();
                    }
                } else {
                    if (event.text.unicode == 8) {
                        name = name.substring(0, name.getSize() - 1);
                    } else if (event.text.unicode == 13) {
                        finName += toupper(name[0]);
                        for (int i = 1; i < name.getSize(); i++) {
                            finName += tolower(name[i]);
                        }
                        gameStart = true;
                        window.close();
                    }
                }
            }
        }

        window.clear(sf::Color::Blue);
        input.setString(name + "|");
        setText(input, window.getSize().x/2.0f, window.getSize().y/2.0f - 45.0f);
        window.draw(title);
        window.draw(prompt);
        window.draw(input);
        window.display();
    }
    return pair<bool,string>(gameStart, finName);
}
void gameWindow(string name) {
    string cols;
    string rows;
    string mines;

    fstream config;
    config.open("files/board_config.cfg", ios_base::in);


    getline(config, cols);
    getline(config, rows);
    getline(config, mines);

    int icol = stoi(cols);
    int irow = stoi(rows);
    int imines = stoi(mines);

    sf::Sprite face;
    sf::Sprite debug;
    sf::Sprite pausee;
    sf::Sprite leaderboard;
    sf::Sprite minute1;
    sf::Sprite minute2;
    sf::Sprite second1;
    sf::Sprite second2;
    sf::Sprite counter1;
    sf::Sprite counter2;
    sf::Sprite counter3;
    sf::Sprite counter4;

    Leaderboard ssaekki;
    ssaekki.readFromFile();
    Stopwatch watch;
    Stopwatch forPause;

    Board board(irow, icol, imines);
    sf::RenderWindow gameWindow(sf::VideoMode(icol * 32, (irow * 32) + 100), "Minesweeper", sf::Style::Close);
    Texturebank bank;

    face.setTexture(*bank.getTexture("face_happy"));
    debug.setTexture(*bank.getTexture("debug"));
    pausee.setTexture(*bank.getTexture("pause"));
    leaderboard.setTexture((*bank.getTexture("leaderboard")));

    face.setPosition(sf::Vector2f((icol / 2.0f * 32) - 32, 32 * (irow + 0.5f)));
    debug.setPosition(sf::Vector2f((icol * 32) - 304, 32 * (irow + 0.5f)));
    pausee.setPosition(sf::Vector2f((icol * 32) - 240, 32 * (irow + 0.5f)));
    leaderboard.setPosition(sf::Vector2f((icol * 32) - 176, 32 * (irow + 0.5f)));


    bool gamewin = false;
    bool debugging = false;
    bool lose = false;
    bool pause = false;
    bool leader = false;
    bool leaderWin = false;
    int tempClock = 0;
    int pausedClock = 0;

    watch.start();
    while (gameWindow.isOpen()) {
        int mineCount = imines;
        sf::Event event;
        while (gameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gameWindow.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (!lose and !gamewin and !pause and !leader) {
                        for (int i = 0; i < irow; i++) {
                            for (int j = 0; j < icol; j++) {
                                if (sf::Mouse::getPosition(gameWindow).x > j * 32 and
                                    sf::Mouse::getPosition(gameWindow).x < (j + 1) * 32) {
                                    if (sf::Mouse::getPosition(gameWindow).y > i * 32 and
                                        sf::Mouse::getPosition(gameWindow).y < (i + 1) * 32) {
                                        if (!board.getBoard().at(i).at(j).isFlagged and
                                            !board.getBoard().at(i).at(j).isRevealed) {
                                            board.getBoard().at(i).at(j).isRevealed = true;
                                            if (board.getBoard().at(i).at(j).hasMine) {
                                                lose = true;
                                            } else {
                                                board.revealNeighbor(&board.getBoard().at(i).at(j));
                                                gamewin = board.checkWin();
                                                if (gamewin) {
                                                    leaderWin = true;
                                                    leader = true;
                                                }
                                            }

                                        }
                                    }
                                }
                            }
                        }
                    }
                    if (sf::Mouse::getPosition(gameWindow).x > (icol / 2.0f * 32) - 32 and
                        sf::Mouse::getPosition(gameWindow).x < (icol / 2.0f * 32) + 32) {
                        if (sf::Mouse::getPosition(gameWindow).y > 32 * (irow + 0.5f) and
                            sf::Mouse::getPosition(gameWindow).y < 32 * (irow + 0.5f) + 64) {
                            board.reset();
                            watch.start();
                            debugging = false;
                            pausedClock = 0;
                            tempClock = 0;
                            if (pause) {
                                pause = false;
                            }
                            if (lose) {
                                lose = false;
                            }
                            if (gamewin) {
                                gamewin = false;
                            }
                        }
                    }
                    if (!lose and !gamewin) {
                        if (sf::Mouse::getPosition(gameWindow).x > (icol * 32) - 240 and
                            sf::Mouse::getPosition(gameWindow).x < (icol * 32) - 176) {
                            if (sf::Mouse::getPosition(gameWindow).y > 32 * (irow + 0.5f) and
                                sf::Mouse::getPosition(gameWindow).y < 32 * (irow + 0.5f) + 64) {
                                if (!pause) {
                                    pause = true;
                                } else {
                                    pause = false;
                                    watch.start();
                                }
                            }
                        }
                        if (sf::Mouse::getPosition(gameWindow).x > (icol * 32) - 304 and
                            sf::Mouse::getPosition(gameWindow).x < (icol * 32) - 240) {
                            if (sf::Mouse::getPosition(gameWindow).y > 32 * (irow + 0.5f) and
                                sf::Mouse::getPosition(gameWindow).y < 32 * (irow + 0.5f) + 64) {
                                if (!debugging)
                                    debugging = true;
                                else
                                    debugging = false;
                            }
                    }
                }
                    if (sf::Mouse::getPosition(gameWindow).x > (icol * 32) - 176 and
                        sf::Mouse::getPosition(gameWindow).x < (icol * 32) - 112) {
                        if (sf::Mouse::getPosition(gameWindow).y > 32 * (irow + 0.5f) and
                            sf::Mouse::getPosition(gameWindow).y < 32 * (irow + 0.5f) + 64) {
                            if (!leader) {
                                leader = true;
                            } else {
                                leader = false;
                            }
                        }
                    }
                } else if (event.mouseButton.button == sf::Mouse::Right) {
                    if (!lose and !gamewin and !pause and !leader){
                        for (int i = 0; i < irow; i++) {
                            for (int j = 0; j < icol; j++) {
                                if (sf::Mouse::getPosition(gameWindow).x > j * 32 and
                                    sf::Mouse::getPosition(gameWindow).x < (j + 1) * 32) {
                                    if (sf::Mouse::getPosition(gameWindow).y > i * 32 and
                                        sf::Mouse::getPosition(gameWindow).y < (i + 1) * 32) {
                                        if (!board.getBoard().at(i).at(j).isFlagged and
                                            !board.getBoard().at(i).at(j).isRevealed) {
                                            board.getBoard().at(i).at(j).isFlagged = true;
                                        } else {
                                            board.getBoard().at(i).at(j).isFlagged = false;
                                        }

                                    }
                                }
                            }
                        }
                    }

                }
            }
        }
        int count = 0;
        gameWindow.clear(sf::Color::White);
        for (int i = 0; i < irow; i++) {
            for (int j = 0; j < icol; j++) {
                if (!pause and !leader) {
                    if (!board.getBoard().at(i).at(j).isRevealed) {
                        board.getBoard().at(i).at(j).visual.setTexture(*bank.getTexture("tile_hidden"));
                        board.getBoard().at(i).at(j).visual.setPosition(sf::Vector2f(j * 32, i * 32));
                        gameWindow.draw(board.getBoard().at(i).at(j).visual);
                    }
                    if (board.getBoard().at(i).at(j).isRevealed) {
                        switch (board.countMines(board.getBoard().at(i).at(j))) {
                            case 0:
                                board.getBoard().at(i).at(j).visual.setTexture(*bank.getTexture("tile_revealed"));
                                board.getBoard().at(i).at(j).visual.setPosition(sf::Vector2f(j * 32, i * 32));
                                gameWindow.draw(board.getBoard().at(i).at(j).visual);
                                break;
                            case 1:
                                board.getBoard().at(i).at(j).visual.setTexture(*bank.getTexture("tile_revealed"));
                                board.getBoard().at(i).at(j).number.setTexture(*bank.getTexture("1"));
                                board.getBoard().at(i).at(j).visual.setPosition(sf::Vector2f(j * 32, i * 32));
                                board.getBoard().at(i).at(j).number.setPosition(sf::Vector2f(j * 32, i * 32));
                                gameWindow.draw(board.getBoard().at(i).at(j).visual);
                                gameWindow.draw(board.getBoard().at(i).at(j).number);
                                break;
                            case 2:
                                board.getBoard().at(i).at(j).visual.setTexture(*bank.getTexture("tile_revealed"));
                                board.getBoard().at(i).at(j).number.setTexture(*bank.getTexture("2"));
                                board.getBoard().at(i).at(j).visual.setPosition(sf::Vector2f(j * 32, i * 32));
                                board.getBoard().at(i).at(j).number.setPosition(sf::Vector2f(j * 32, i * 32));
                                gameWindow.draw(board.getBoard().at(i).at(j).visual);
                                gameWindow.draw(board.getBoard().at(i).at(j).number);
                                break;
                            case 3:
                                board.getBoard().at(i).at(j).visual.setTexture(*bank.getTexture("tile_revealed"));
                                board.getBoard().at(i).at(j).number.setTexture(*bank.getTexture("3"));
                                board.getBoard().at(i).at(j).visual.setPosition(sf::Vector2f(j * 32, i * 32));
                                board.getBoard().at(i).at(j).number.setPosition(sf::Vector2f(j * 32, i * 32));
                                gameWindow.draw(board.getBoard().at(i).at(j).visual);
                                gameWindow.draw(board.getBoard().at(i).at(j).number);
                                break;
                            case 4:
                                board.getBoard().at(i).at(j).visual.setTexture(*bank.getTexture("tile_revealed"));
                                board.getBoard().at(i).at(j).number.setTexture(*bank.getTexture("4"));
                                board.getBoard().at(i).at(j).visual.setPosition(sf::Vector2f(j * 32, i * 32));
                                board.getBoard().at(i).at(j).number.setPosition(sf::Vector2f(j * 32, i * 32));
                                gameWindow.draw(board.getBoard().at(i).at(j).visual);
                                gameWindow.draw(board.getBoard().at(i).at(j).number);
                                break;
                            case 5:
                                board.getBoard().at(i).at(j).visual.setTexture(*bank.getTexture("tile_revealed"));
                                board.getBoard().at(i).at(j).number.setTexture(*bank.getTexture("5"));
                                board.getBoard().at(i).at(j).visual.setPosition(sf::Vector2f(j * 32, i * 32));
                                board.getBoard().at(i).at(j).number.setPosition(sf::Vector2f(j * 32, i * 32));
                                gameWindow.draw(board.getBoard().at(i).at(j).visual);
                                gameWindow.draw(board.getBoard().at(i).at(j).number);
                                break;
                            case 6:
                                board.getBoard().at(i).at(j).visual.setTexture(*bank.getTexture("tile_revealed"));
                                board.getBoard().at(i).at(j).number.setTexture(*bank.getTexture("6"));
                                board.getBoard().at(i).at(j).visual.setPosition(sf::Vector2f(j * 32, i * 32));
                                board.getBoard().at(i).at(j).number.setPosition(sf::Vector2f(j * 32, i * 32));
                                gameWindow.draw(board.getBoard().at(i).at(j).visual);
                                gameWindow.draw(board.getBoard().at(i).at(j).number);
                                break;
                            case 7:
                                board.getBoard().at(i).at(j).visual.setTexture(*bank.getTexture("tile_revealed"));
                                board.getBoard().at(i).at(j).number.setTexture(*bank.getTexture("7"));
                                board.getBoard().at(i).at(j).visual.setPosition(sf::Vector2f(j * 32, i * 32));
                                board.getBoard().at(i).at(j).number.setPosition(sf::Vector2f(j * 32, i * 32));
                                gameWindow.draw(board.getBoard().at(i).at(j).visual);
                                gameWindow.draw(board.getBoard().at(i).at(j).number);
                                break;
                            case 8:
                                board.getBoard().at(i).at(j).visual.setTexture(*bank.getTexture("tile_revealed"));
                                board.getBoard().at(i).at(j).number.setTexture(*bank.getTexture("8"));
                                board.getBoard().at(i).at(j).visual.setPosition(sf::Vector2f(j * 32, i * 32));
                                board.getBoard().at(i).at(j).number.setPosition(sf::Vector2f(j * 32, i * 32));
                                gameWindow.draw(board.getBoard().at(i).at(j).visual);
                                gameWindow.draw(board.getBoard().at(i).at(j).number);
                                break;
                        }
                    }
                    if (board.getBoard().at(i).at(j).isFlagged) {
                        count += 1;
                        if (!lose) {
                            board.getBoard().at(i).at(j).flag.setTexture(*bank.getTexture("flag"));
                            board.getBoard().at(i).at(j).flag.setPosition(sf::Vector2f(j * 32, i * 32));
                            gameWindow.draw(board.getBoard().at(i).at(j).flag);
                        }
                    }
                    if (board.getBoard().at(i).at(j).hasMine and board.getBoard().at(i).at(j).isRevealed) {
                        board.getBoard().at(i).at(j).visual.setTexture(*bank.getTexture("tile_revealed"));
                        board.getBoard().at(i).at(j).visual.setPosition(sf::Vector2f(j * 32, i * 32));
                        board.getBoard().at(i).at(j).mine.setTexture(*bank.getTexture("mine"));
                        board.getBoard().at(i).at(j).mine.setPosition(sf::Vector2f(j * 32, i * 32));
                        gameWindow.draw(board.getBoard().at(i).at(j).visual);
                        gameWindow.draw(board.getBoard().at(i).at(j).mine);
                    }
                    if (!gamewin and debugging) {
                        if (board.getBoard().at(i).at(j).hasMine and !board.getBoard().at(i).at(j).isRevealed) {
                            board.getBoard().at(i).at(j).visual.setTexture(*bank.getTexture("tile_hidden"));
                            board.getBoard().at(i).at(j).visual.setPosition(sf::Vector2f(j * 32, i * 32));
                            board.getBoard().at(i).at(j).mine.setTexture(*bank.getTexture("mine"));
                            board.getBoard().at(i).at(j).mine.setPosition(sf::Vector2f(j * 32, i * 32));
                            gameWindow.draw(board.getBoard().at(i).at(j).visual);
                            gameWindow.draw(board.getBoard().at(i).at(j).mine);
                        }
                    } else if (gamewin) {
                        if (board.getBoard().at(i).at(j).hasMine) {
                            board.getBoard().at(i).at(j).isFlagged = true;
                        }
                    } else if (lose) {
                        if (board.getBoard().at(i).at(j).hasMine) {
                            board.getBoard().at(i).at(j).mine.setTexture(*bank.getTexture("mine"));
                            board.getBoard().at(i).at(j).mine.setPosition(sf::Vector2f(j * 32, i * 32));
                            gameWindow.draw(board.getBoard().at(i).at(j).mine);
                        }
                    }
                } else {
                        board.getBoard().at(i).at(j).visual.setTexture(*bank.getTexture("tile_revealed"));
                        board.getBoard().at(i).at(j).visual.setPosition(sf::Vector2f(j * 32, i * 32));
                        gameWindow.draw(board.getBoard().at(i).at(j).visual);
                }
            }
        }
        mineCount -= count;
        if (lose) {
            face.setTexture(*bank.getTexture("face_lose"));
            gameWindow.draw(face);
        } else if (gamewin) {
            face.setTexture(*bank.getTexture("face_win"));
            gameWindow.draw(face);

        } else {
            face.setTexture(*bank.getTexture("face_happy"));
            gameWindow.draw(face);
        }
        if (pause) {
            pausee.setTexture(*bank.getTexture("play"));
        } else {
            pausee.setTexture(*bank.getTexture("pause"));
        }
        if (!lose and !gamewin and !pause and !leader) {
            watch.stop();
            tempClock = pausedClock + watch.getDuration();
            switch (tempClock % 10) {
                case 0:
                    second2.setTexture(*bank.getTexture("digits"));
                    second2.setTextureRect(sf::IntRect(0, 0, 21, 32));
                    second2.setPosition(sf::Vector2f((icol * 32) - 33, 32 * ((float)irow+0.5f) +16));
                    break;
                case 1:
                    second2.setTexture(*bank.getTexture("digits"));
                    second2.setTextureRect(sf::IntRect(21, 0, 21, 32));
                    second2.setPosition(sf::Vector2f((icol * 32) - 33, 32 * ((float)irow+0.5f) +16));
                    break;
                case 2:
                    second2.setTexture(*bank.getTexture("digits"));
                    second2.setTextureRect(sf::IntRect(42, 0, 21, 32));
                    second2.setPosition(sf::Vector2f((icol * 32) - 33, 32 * ((float)irow+0.5f) +16));
                    break;
                case 3:
                    second2.setTexture(*bank.getTexture("digits"));
                    second2.setTextureRect(sf::IntRect(63, 0, 21, 32));
                    second2.setPosition(sf::Vector2f((icol * 32) - 33, 32 * ((float)irow+0.5f) +16));
                    break;
                case 4:
                    second2.setTexture(*bank.getTexture("digits"));
                    second2.setTextureRect(sf::IntRect(84, 0, 21, 32));
                    second2.setPosition(sf::Vector2f((icol * 32) - 33, 32 * ((float)irow+0.5f) +16));
                    break;
                case 5:
                    second2.setTexture(*bank.getTexture("digits"));
                    second2.setTextureRect(sf::IntRect(105, 0, 21, 32));
                    second2.setPosition(sf::Vector2f((icol * 32) - 33, 32 * ((float)irow+0.5f) +16));
                    break;
                case 6:
                    second2.setTexture(*bank.getTexture("digits"));
                    second2.setTextureRect(sf::IntRect(126, 0, 21, 32));
                    second2.setPosition(sf::Vector2f((icol * 32) - 33, 32 * ((float)irow+0.5f) +16));
                    break;
                case 7:
                    second2.setTexture(*bank.getTexture("digits"));
                    second2.setTextureRect(sf::IntRect(147, 0, 21, 32));
                    second2.setPosition(sf::Vector2f((icol * 32) - 33, 32 * ((float)irow+0.5f) +16));
                    break;
                case 8:
                    second2.setTexture(*bank.getTexture("digits"));
                    second2.setTextureRect(sf::IntRect(168, 0, 21, 32));
                    second2.setPosition(sf::Vector2f((icol * 32) - 33, 32 * ((float)irow+0.5f) +16));
                    break;
                case 9:
                    second2.setTexture(*bank.getTexture("digits"));
                    second2.setTextureRect(sf::IntRect(189, 0, 21, 32));
                    second2.setPosition(sf::Vector2f((icol * 32) - 33, 32 * ((float)irow+0.5f) +16));
                    break;

            }
            switch (((tempClock / 10) % 6)) {
                case 0:
                    second1.setTexture(*bank.getTexture("digits"));
                    second1.setTextureRect(sf::IntRect(0, 0, 21, 32));
                    second1.setPosition(sf::Vector2f((icol * 32) - 54, 32 * ((float)irow+0.5f) +16));
                    break;
                case 1:
                    second1.setTexture(*bank.getTexture("digits"));
                    second1.setTextureRect(sf::IntRect(21, 0, 21, 32));
                    second1.setPosition(sf::Vector2f((icol * 32) - 54, 32 * ((float)irow+0.5f) +16));
                    break;
                case 2:
                    second1.setTexture(*bank.getTexture("digits"));
                    second1.setTextureRect(sf::IntRect(42, 0, 21, 32));
                    second1.setPosition(sf::Vector2f((icol * 32) - 54, 32 * ((float)irow+0.5f) +16));
                    break;
                case 3:
                    second1.setTexture(*bank.getTexture("digits"));
                    second1.setTextureRect(sf::IntRect(63, 0, 21, 32));
                    second1.setPosition(sf::Vector2f((icol * 32) - 54, 32 * ((float)irow+0.5f) +16));
                    break;
                case 4:
                    second1.setTexture(*bank.getTexture("digits"));
                    second1.setTextureRect(sf::IntRect(84, 0, 21, 32));
                    second1.setPosition(sf::Vector2f((icol * 32) - 54, 32 * ((float)irow+0.5f) +16));
                    break;
                case 5:
                    second1.setTexture(*bank.getTexture("digits"));
                    second1.setTextureRect(sf::IntRect(105, 0, 21, 32));
                    second1.setPosition(sf::Vector2f((icol * 32) - 54, 32 * ((float)irow+0.5f) +16));
                    break;
            }
            switch ((tempClock / 60) % 10) {
                case 0:
                    minute2.setTexture(*bank.getTexture("digits"));
                    minute2.setTextureRect(sf::IntRect(0, 0, 21, 32));
                    minute2.setPosition(sf::Vector2f((icol * 32) - 76, 32 * ((float)irow+0.5f) +16));
                    break;
                case 1:
                    minute2.setTexture(*bank.getTexture("digits"));
                    minute2.setTextureRect(sf::IntRect(21, 0, 21, 32));
                    minute2.setPosition(sf::Vector2f((icol * 32) - 76, 32 * ((float)irow+0.5f) +16));
                    break;
                case 2:
                    minute2.setTexture(*bank.getTexture("digits"));
                    minute2.setTextureRect(sf::IntRect(42, 0, 21, 32));
                    minute2.setPosition(sf::Vector2f((icol * 32) - 76, 32 * ((float)irow+0.5f) +16));
                    break;
                case 3:
                    minute2.setTexture(*bank.getTexture("digits"));
                    minute2.setTextureRect(sf::IntRect(63, 0, 21, 32));
                    minute2.setPosition(sf::Vector2f((icol * 32) - 76, 32 * ((float)irow+0.5f) +16));
                    break;
                case 4:
                    minute2.setTexture(*bank.getTexture("digits"));
                    minute2.setTextureRect(sf::IntRect(84, 0, 21, 32));
                    minute2.setPosition(sf::Vector2f((icol * 32) - 76, 32 * ((float)irow+0.5f) +16));
                    break;
                case 5:
                    minute2.setTexture(*bank.getTexture("digits"));
                    minute2.setTextureRect(sf::IntRect(105, 0, 21, 32));
                    minute2.setPosition(sf::Vector2f((icol * 32) - 76, 32 * ((float)irow+0.5f) +16));
                    break;
                case 6:
                    minute2.setTexture(*bank.getTexture("digits"));
                    minute2.setTextureRect(sf::IntRect(126, 0, 21, 32));
                    minute2.setPosition(sf::Vector2f((icol * 32) - 76, 32 * ((float)irow+0.5f) +16));
                    break;
                case 7:
                    minute2.setTexture(*bank.getTexture("digits"));
                    minute2.setTextureRect(sf::IntRect(147, 0, 21, 32));
                    minute2.setPosition(sf::Vector2f((icol * 32) - 76, 32 * ((float)irow+0.5f) +16));
                    break;
                case 8:
                    minute2.setTexture(*bank.getTexture("digits"));
                    minute2.setTextureRect(sf::IntRect(168, 0, 21, 32));
                    minute2.setPosition(sf::Vector2f((icol * 32) - 76, 32 * ((float)irow+0.5f) +16));
                    break;
                case 9:
                    minute2.setTexture(*bank.getTexture("digits"));
                    minute2.setTextureRect(sf::IntRect(189, 0, 21, 32));
                    minute2.setPosition(sf::Vector2f((icol * 32) - 76, 32 * ((float)irow+0.5f) +16));
                    break;

            }
            switch (((tempClock / 60) / 10) % 10) {
                case 0:
                    minute1.setTexture(*bank.getTexture("digits"));
                    minute1.setTextureRect(sf::IntRect(0, 0, 21, 32));
                    minute1.setPosition(sf::Vector2f((icol * 32) - 97, 32 * ((float)irow+0.5f) +16));
                    break;
                case 1:
                    minute1.setTexture(*bank.getTexture("digits"));
                    minute1.setTextureRect(sf::IntRect(21, 0, 21, 32));
                    minute1.setPosition(sf::Vector2f((icol * 32) - 97, 32 * ((float)irow+0.5f) +16));
                    break;
                case 2:
                    minute1.setTexture(*bank.getTexture("digits"));
                    minute1.setTextureRect(sf::IntRect(42, 0, 21, 32));
                    minute1.setPosition(sf::Vector2f((icol * 32) - 97, 32 * ((float)irow+0.5f) +16));
                    break;
                case 3:
                    minute1.setTexture(*bank.getTexture("digits"));
                    minute1.setTextureRect(sf::IntRect(63, 0, 21, 32));
                    minute1.setPosition(sf::Vector2f((icol * 32) - 97, 32 * ((float)irow+0.5f) +16));
                    break;
                case 4:
                    minute1.setTexture(*bank.getTexture("digits"));
                    minute1.setTextureRect(sf::IntRect(84, 0, 21, 32));
                    minute1.setPosition(sf::Vector2f((icol * 32) - 97, 32 * ((float)irow+0.5f) +16));
                    break;
                case 5:
                    minute1.setTexture(*bank.getTexture("digits"));
                    minute1.setTextureRect(sf::IntRect(105, 0, 21, 32));
                    minute1.setPosition(sf::Vector2f((icol * 32) - 97, 32 * ((float)irow+0.5f) +16));
                    break;
                case 6:
                    minute1.setTexture(*bank.getTexture("digits"));
                    minute1.setTextureRect(sf::IntRect(126, 0, 21, 32));
                    minute1.setPosition(sf::Vector2f((icol * 32) - 97, 32 * ((float)irow+0.5f) +16));
                    break;
                case 7:
                    minute1.setTexture(*bank.getTexture("digits"));
                    minute1.setTextureRect(sf::IntRect(147, 0, 21, 32));
                    minute1.setPosition(sf::Vector2f((icol * 32) - 97, 32 * ((float)irow+0.5f) +16));
                    break;
                case 8:
                    minute1.setTexture(*bank.getTexture("digits"));
                    minute1.setTextureRect(sf::IntRect(168, 0, 21, 32));
                    minute1.setPosition(sf::Vector2f((icol * 32) - 97, 32 * ((float)irow+0.5f) +16));
                    break;
                case 9:
                    minute1.setTexture(*bank.getTexture("digits"));
                    minute1.setTextureRect(sf::IntRect(189, 0, 21, 32));
                    minute1.setPosition(sf::Vector2f((icol * 32) - 97, 32 * ((float)irow+0.5f) +16));
                    break;

            }
        } else {
            pausedClock = tempClock;
        }
        switch (abs(mineCount % 10)) {
            case 0:
                counter2.setTexture(*bank.getTexture("digits"));
                counter2.setTextureRect(sf::IntRect(0, 0, 21, 32));
                counter2.setPosition(sf::Vector2f(75, 32 * ((float)irow+0.5f) +16));
                break;
            case 1:
                counter2.setTexture(*bank.getTexture("digits"));
                counter2.setTextureRect(sf::IntRect(21, 0, 21, 32));
                counter2.setPosition(sf::Vector2f(75, 32 * ((float)irow+0.5f) +16));
                break;
            case 2:
                counter2.setTexture(*bank.getTexture("digits"));
                counter2.setTextureRect(sf::IntRect(42, 0, 21, 32));
                counter2.setPosition(sf::Vector2f(75, 32 * ((float)irow+0.5f) +16));
                break;
            case 3:
                counter2.setTexture(*bank.getTexture("digits"));
                counter2.setTextureRect(sf::IntRect(63, 0, 21, 32));
                counter2.setPosition(sf::Vector2f(75, 32 * ((float)irow+0.5f) +16));
                break;
            case 4:
                counter2.setTexture(*bank.getTexture("digits"));
                counter2.setTextureRect(sf::IntRect(84, 0, 21, 32));
                counter2.setPosition(sf::Vector2f(75, 32 * ((float)irow+0.5f) +16));
                break;
            case 5:
                counter2.setTexture(*bank.getTexture("digits"));
                counter2.setTextureRect(sf::IntRect(105, 0, 21, 32));
                counter2.setPosition(sf::Vector2f(75, 32 * ((float)irow+0.5f) +16));
                break;
            case 6:
                counter2.setTexture(*bank.getTexture("digits"));
                counter2.setTextureRect(sf::IntRect(126, 0, 21, 32));
                counter2.setPosition(sf::Vector2f(75, 32 * ((float)irow+0.5f) +16));
                break;
            case 7:
                counter2.setTexture(*bank.getTexture("digits"));
                counter2.setTextureRect(sf::IntRect(147, 0, 21, 32));
                counter2.setPosition(sf::Vector2f(75, 32 * ((float)irow+0.5f) +16));
                break;
            case 8:
                counter2.setTexture(*bank.getTexture("digits"));
                counter2.setTextureRect(sf::IntRect(168, 0, 21, 32));
                counter2.setPosition(sf::Vector2f(75, 32 * ((float)irow+0.5f) +16));
                break;
            case 9:
                counter2.setTexture(*bank.getTexture("digits"));
                counter2.setTextureRect(sf::IntRect(189, 0, 21, 32));
                counter2.setPosition(sf::Vector2f(75, 32 * ((float)irow+0.5f) +16));
                break;

        }
        switch (abs((mineCount / 10) % 10)) {
            case 0:
                counter3.setTexture(*bank.getTexture("digits"));
                counter3.setTextureRect(sf::IntRect(0, 0, 21, 32));
                counter3.setPosition(sf::Vector2f(54, 32 * ((float)irow+0.5f) +16));
                break;
            case 1:
                counter3.setTexture(*bank.getTexture("digits"));
                counter3.setTextureRect(sf::IntRect(21, 0, 21, 32));
                counter3.setPosition(sf::Vector2f(54, 32 * ((float)irow+0.5f) +16));
                break;
            case 2:
                counter3.setTexture(*bank.getTexture("digits"));
                counter3.setTextureRect(sf::IntRect(42, 0, 21, 32));
                counter3.setPosition(sf::Vector2f(54, 32 * ((float)irow+0.5f) +16));
                break;
            case 3:
                counter3.setTexture(*bank.getTexture("digits"));
                counter3.setTextureRect(sf::IntRect(63, 0, 21, 32));
                counter3.setPosition(sf::Vector2f(54, 32 * ((float)irow+0.5f) +16));
                break;
            case 4:
                counter3.setTexture(*bank.getTexture("digits"));
                counter3.setTextureRect(sf::IntRect(84, 0, 21, 32));
                counter3.setPosition(sf::Vector2f(54, 32 * ((float)irow+0.5f) +16));
                break;
            case 5:
                counter3.setTexture(*bank.getTexture("digits"));
                counter3.setTextureRect(sf::IntRect(105, 0, 21, 32));
                counter3.setPosition(sf::Vector2f(54, 32 * ((float)irow+0.5f) +16));
                break;
            case 6:
                counter3.setTexture(*bank.getTexture("digits"));
                counter3.setTextureRect(sf::IntRect(126, 0, 21, 32));
                counter3.setPosition(sf::Vector2f(54, 32 * ((float)irow+0.5f) +16));
                break;
            case 7:
                counter3.setTexture(*bank.getTexture("digits"));
                counter3.setTextureRect(sf::IntRect(147, 0, 21, 32));
                counter3.setPosition(sf::Vector2f(54, 32 * ((float)irow+0.5f) +16));
                break;
            case 8:
                counter3.setTexture(*bank.getTexture("digits"));
                counter3.setTextureRect(sf::IntRect(168, 0, 21, 32));
                counter3.setPosition(sf::Vector2f(54, 32 * ((float)irow+0.5f) +16));
                break;
            case 9:
                counter3.setTexture(*bank.getTexture("digits"));
                counter3.setTextureRect(sf::IntRect(189, 0, 21, 32));
                counter3.setPosition(sf::Vector2f(54, 32 * ((float)irow+0.5f) +16));
                break;
        }
        if (mineCount >= 0) {
            switch (abs((mineCount / 100) % 10)) {
                case 0:
                    counter1.setTexture(*bank.getTexture("digits"));
                    counter1.setTextureRect(sf::IntRect(0, 0, 21, 32));
                    counter1.setPosition(sf::Vector2f(33, 32 * ((float) irow + 0.5f) + 16));
                    break;
                case 1:
                    counter1.setTexture(*bank.getTexture("digits"));
                    counter1.setTextureRect(sf::IntRect(21, 0, 21, 32));
                    counter1.setPosition(sf::Vector2f(33, 32 * ((float) irow + 0.5f) + 16));
                    break;
                case 2:
                    counter1.setTexture(*bank.getTexture("digits"));
                    counter1.setTextureRect(sf::IntRect(42, 0, 21, 32));
                    counter1.setPosition(sf::Vector2f(33, 32 * ((float) irow + 0.5f) + 16));
                    break;
                case 3:
                    counter1.setTexture(*bank.getTexture("digits"));
                    counter1.setTextureRect(sf::IntRect(63, 0, 21, 32));
                    counter1.setPosition(sf::Vector2f(33, 32 * ((float) irow + 0.5f) + 16));
                    break;
                case 4:
                    counter1.setTexture(*bank.getTexture("digits"));
                    counter1.setTextureRect(sf::IntRect(84, 0, 21, 32));
                    counter1.setPosition(sf::Vector2f(33, 32 * ((float) irow + 0.5f) + 16));
                    break;
                case 5:
                    counter1.setTexture(*bank.getTexture("digits"));
                    counter1.setTextureRect(sf::IntRect(105, 0, 21, 32));
                    counter1.setPosition(sf::Vector2f(33, 32 * ((float) irow + 0.5f) + 16));
                    break;
                case 6:
                    counter1.setTexture(*bank.getTexture("digits"));
                    counter1.setTextureRect(sf::IntRect(126, 0, 21, 32));
                    counter1.setPosition(sf::Vector2f(33, 32 * ((float) irow + 0.5f) + 16));
                    break;
                case 7:
                    counter1.setTexture(*bank.getTexture("digits"));
                    counter1.setTextureRect(sf::IntRect(147, 0, 21, 32));
                    counter1.setPosition(sf::Vector2f(33, 32 * ((float) irow + 0.5f) + 16));
                    break;
                case 8:
                    counter1.setTexture(*bank.getTexture("digits"));
                    counter1.setTextureRect(sf::IntRect(168, 0, 21, 32));
                    counter1.setPosition(sf::Vector2f(33, 32 * ((float) irow + 0.5f) + 16));
                    break;
                case 9:
                    counter1.setTexture(*bank.getTexture("digits"));
                    counter1.setTextureRect(sf::IntRect(189, 0, 21, 32));
                    counter1.setPosition(sf::Vector2f(33, 32 * ((float) irow + 0.5f) + 16));
                    break;
            }
        } else {
            counter4.setTexture(*bank.getTexture("digits"));
            counter4.setTextureRect(sf::IntRect(210, 0, 21, 32));
            counter4.setPosition(sf::Vector2f(12, 32 * ((float)irow+0.5f) +16));
            gameWindow.draw(counter4);
        }
        if (leaderWin and leader) {
            counter2.setTexture(*bank.getTexture("digits"));
            counter2.setTextureRect(sf::IntRect(0, 0, 21, 32));
            counter2.setPosition(sf::Vector2f(75, 32 * ((float)irow+0.5f) +16));
            counter3.setTexture(*bank.getTexture("digits"));
            counter3.setTextureRect(sf::IntRect(0, 0, 21, 32));
            counter3.setPosition(sf::Vector2f(54, 32 * ((float)irow+0.5f) +16));
            counter1.setTexture(*bank.getTexture("digits"));
            counter1.setTextureRect(sf::IntRect(0, 0, 21, 32));
            counter1.setPosition(sf::Vector2f(33, 32 * ((float) irow + 0.5f) + 16));
            gameWindow.draw(minute1);
            gameWindow.draw(minute2);
            gameWindow.draw(second2);
            gameWindow.draw(second1);
            gameWindow.draw(counter3);
            gameWindow.draw(counter2);
            gameWindow.draw(counter1);
            gameWindow.draw(debug);
            gameWindow.draw(pausee);
            gameWindow.draw(leaderboard);
            gameWindow.display();
            ssaekki.writeToFile(to_string(((tempClock / 60) / 10) % 10) + to_string((tempClock / 60) % 10) + ":" + to_string(((tempClock / 10) % 6)) + to_string(((tempClock % 10))), name);
            leaderWindow(icol, irow, leader, leaderWin, watch, ssaekki, name);
        }
        gameWindow.draw(minute1);
        gameWindow.draw(minute2);
        gameWindow.draw(second2);
        gameWindow.draw(second1);
        gameWindow.draw(counter3);
        gameWindow.draw(counter2);
        gameWindow.draw(counter1);
        gameWindow.draw(debug);
        gameWindow.draw(pausee);
        gameWindow.draw(leaderboard);
        gameWindow.display();
        if (leader and !leaderWin) {
            leaderWindow(icol, irow, leader, leaderWin, watch, ssaekki, name);
        }
    }
}

void leaderWindow(int icol, int irow, bool& leader, bool& gamewin, Stopwatch& watch, Leaderboard& ssaekki, string name) {
    sf::Text title;
    sf::Text people;

    string toDisplay;

    sf::Font LEADERFONTS;
    LEADERFONTS.loadFromFile("files/font.ttf");
    sf::RenderWindow leaderb(sf::VideoMode(16 * icol, (16 * irow) + 50), "Minesweeper", sf::Style::Close);

    setEverything(title, LEADERFONTS, "UB", "white", 20);
    setEverything(people, LEADERFONTS, "B", "white", 18);

    title.setString("LEADERBOARD");
    setText(title, leaderb.getSize().x/2.0f, leaderb.getSize().x/2.0f - 120);

    if (gamewin) {
        ssaekki.readFromFile(name);
    } else {
        ssaekki.readFromFile();
    }


    ofstream stream("files/leaderboard.txt");

    int j = 0;

    for (auto i = ssaekki.leaderboard.begin(); i != ssaekki.leaderboard.end(); i++) {
        if (j == 5){
            break;
        }
        toDisplay += to_string(i->second.first) + ".\t" + i->first + "\t" + i->second.second + "\n\n";
        if (j != 4) {
            if (i->second.second[i->second.second.size() - 1] == '*') {
                stream <<  i->first + "," + i->second.second.substr(0, i->second.second.size()-1) << endl;
            } else {
                stream <<  i->first + "," + i->second.second << endl;
            }

        } else {
            if (i->second.second[i->second.second.size() - 1] == '*') {
                stream <<  i->first + "," + i->second.second.substr(0, i->second.second.size()-1);
            } else {
                stream <<  i->first + "," + i->second.second;
            }
        }
        j++;
    }

    people.setString(toDisplay);
    setText(people, leaderb.getSize().x/2.0f, leaderb.getSize().x/2.0f + 20);

    while (leaderb.isOpen()) {
        leaderb.clear(sf::Color::Blue);
        leaderb.draw(title);
        leaderb.draw(people);
        leaderb.display();
        sf::Event event;
        while (leaderb.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                leaderb.close();
                leader = false;
                gamewin = false;
                watch.start();
            }
        }
    }
}