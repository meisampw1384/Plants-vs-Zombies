#include "game.h"
#include "ui_game.h"
#include <QMessageBox>
#include <QDebug>
#include <QJsonDocument>

// Constructor
game::game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::game)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    timer = new QTimer(this);
    remainingTime = 210;

    connect(timer, &QTimer::timeout, this, &game::updateCountdown);
    connect(socket, &QTcpSocket::readyRead, this, &game::onReadyRead);
    connect(socket, &QTcpSocket::connected, this, &game::onConnected);
    connect(socket, &QTcpSocket::disconnected, this, &game::onDisconnected);

    setupUI();

    timer->start(1000);
}

// Destructor
game::~game()
{
    delete ui;
}

// Slot when connected to the server
void game::onConnected()
{
    socket->connectToHost(ip, port);
    qDebug() << "Connected to server";
    QJsonObject request;
    request["action"] = "set_role";
    request["role"] = role;
}

// Slot when disconnected from the server
void game::onDisconnected()
{
    qDebug() << "Disconnected from server";
    QMessageBox::warning(this, "Disconnected", "Disconnected from server.");
}

// Update countdown timer
void game::updateCountdown()
{
    if (remainingTime > 0) {
        remainingTime--;
        int minutes = remainingTime / 60;
        int seconds = remainingTime % 60;
        ui->remaining_time_label->setText(QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0')));
    } else {
        timer->stop();
        QMessageBox::information(this, "Game Over", "The game has ended!");
    }
}

void game::onReadyRead()
{
    QByteArray data = socket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject response = doc.object();

    processResponse(response);
}

// Process server response
void game::processResponse(const QJsonObject &response)
{
    QString action = response["action"].toString();
    qDebug() << "cc get data";
    Characters *ch = nullptr;
    if (action == "add_char")
    qDebug() << response["character"];
    {
        switch (response["character"].toInt()) {
        case 1:
            ch = new zombies(response["x"].toInt(), response["y"].toInt(), 500, 30, "tall", "can move over walnut and move quickly", 1, 1);
            break;
        case 2:
            ch = new zombies(response["x"].toInt(), response["y"].toInt(), 500, 25, "regular", "basic zombie with average abilities", 1, 1);
            break;
        case 3:
            ch = new zombies(response["x"].toInt(), response["y"].toInt(), 4000, 75, "purplehair", "very powerful zombie", 1, 0.5);
            break;
        case 4:
            ch = new zombies(response["x"].toInt(), response["y"].toInt(), 800, 25, "leafhead", "leaves on the head make more resilient", 1, 1);
            break;
        case 5:
            ch = new zombies(response["x"].toInt(), response["y"].toInt(), 1950, 50, "buckethead", "wears a bucket on his head, giving it extra health", 2, 1);
            break;
        case 6:
            ch = new zombies(response["x"].toInt(), response["y"].toInt(), 500, 20, "astronaut", "speeds up after health becomes 100", 1, 1);
            break;
        case 7:
            ch = new plants(response["x"].toInt(), response["y"].toInt(), 200, 30, 1, "boomerang", "all zombies on the same row of the boomerang will lose 15 of their health");
            break;
        case 8:
            ch = new plants(response["x"].toInt(), response["y"].toInt(), 0, 0, 300, "jalpeno", "zombies who are in the same row as jalapeno will lose 300 of their health");
            break;
        case 9:
            ch = new plants(response["x"].toInt(), response["y"].toInt(), 200, 15, 1, "peashooter", "basic plant that shoots peas at zombies regularly");
            break;
        case 10:
            ch = new plants(response["x"].toInt(), response["y"].toInt(), 200, 40, 1, "twopeashooter", "more powerful than basic shooter");
            break;
        case 11:
            ch = new plants(response["x"].toInt(), response["y"].toInt(), 400, 0, 0, "walnut", "acts as armor and stops zombies");
            break;
        case 12:
            ch = new plants(response["x"].toInt(), response["y"].toInt(), 0, 500, 0, "plummine", "those who are in the two squares of the bomb will lose 200 health");
            break;
        default:
            return;
        }
    }
    scene->addItem(ch);
}

// Setter methods
void game::set_ip(QString _ip)
{
    ip = _ip;
    qDebug() << ip;
}

void game::set_port(int _port) {
    port = _port;
    qDebug() << port;
}

void game::set_role(QString _role)
{
    role = _role;
}

// Send move request to the server
void game::sendMoveRequest(const QString &entityType, int entityId, const QString &direction)
{
    QJsonObject request;
    request["action"] = "move";
    request["entity_type"] = entityType;
    request["entity_id"] = entityId;
    request["direction"] = direction;

    QJsonDocument doc(request);
    QByteArray data = doc.toJson();
    socket->write(data);
    socket->flush();
}

// Update the game state based on server response
void game::updateGameState(const QJsonArray &gameState)
{
    // Update the game state in the UI based on the received gameState
    // Example: Update positions of entities on the game field
}


// Setup UI elements
void game::setupUI()
{
    ui->remaining_time_label->setText("3:30");
    scene = new CustomGraphicsScene(this);
    ui->field_view->setScene(scene);

    // Load your background image
    QPixmap backgroundImage("../images/field.png");

    if (backgroundImage.isNull()) {
        qDebug() << "Failed to load background image";
    }
    else {
        // Create a QGraphicsPixmapItem with the background image
        QGraphicsPixmapItem *background = new QGraphicsPixmapItem(backgroundImage);
        background->setPos(30,-20); // Set position at top-left corner of the scene
        scene->addItem(background);
    }

    // Connect scene mouse press event to the slot
    connect(scene, &CustomGraphicsScene::sceneClicked, this, &game::onFieldClicked);

    // Connect button signals to slots
    connect(ui->tall_Z_Pushbutton, &QPushButton::clicked, this, &game::on_tall_Z_Pushbutton_clicked);
    connect(ui->Reg_zombie_pushbutton, &QPushButton::clicked, this, &game::on_Reg_zombie_pushbutton_clicked);
    connect(ui->purple_pushbutton, &QPushButton::clicked, this, &game::on_purple_pushbutton_clicked);
    connect(ui->leaf_Z_pushbutton, &QPushButton::clicked, this, &game::on_leaf_Z_pushbutton_clicked);
    connect(ui->bucket_Z_pushbutton, &QPushButton::clicked, this, &game::on_bucket_Z_pushbutton_clicked);
    connect(ui->astro_Z_pushbutton, &QPushButton::clicked, this, &game::on_astro_Z_pushbutton_clicked);
    connect(ui->boom_Pushbutton, &QPushButton::clicked, this, &game::on_boom_Pushbutton_clicked);
    connect(ui->Jalo_P_button, &QPushButton::clicked, this, &game::on_Jalo_P_button_clicked);
    connect(ui->peashoot_Pushbutton, &QPushButton::clicked, this, &game::on_peashoot_Pushbutton_clicked);
    connect(ui->twopeashoot_Pushbutton, &QPushButton::clicked, this, &game::on_twopeashoot_Pushbutton_clicked);
    connect(ui->wallnut_Pushbutton, &QPushButton::clicked, this, &game::on_wallnut_Pushbutton_clicked);
    connect(ui->Plum_mine_pushbutton, &QPushButton::clicked, this, &game::on_Plum_mine_pushbutton_clicked);

    selectedCharacterType = None;
}

// Slot to handle field clicks
void game::onFieldClicked(const QPointF &position)
{
    // Convert the scene position to grid coordinates
    int x; // Assuming each grid cell is 50x50 pixels
    int y;

    int tmpx = position.x();
    int tmpy = position.y();

    if(tmpx >= 145 and tmpx < 225)
    {
        x = 2;
    }
    else if(tmpx >= 225 and tmpx < 305)
    {
        x = 3;
    }
    else if(tmpx >= 305 and tmpx < 385)
    {
        x = 4;
    }
    else if(tmpx >= 385 and tmpx < 465)
    {
        x = 5;
    }
    else if(tmpx >= 465 and tmpx < 545)
    {
        x = 6;
    }
    else if(tmpx >= 545 and tmpx < 625)
    {
        x = 7;
    }
    else if(tmpx >= 625 and tmpx < 705)
    {
        x = 8;
    }
    else if(tmpx >= 705 and tmpx < 785)
    {
        x = 9;
    }
    else if(tmpx >= 785 and tmpx < 865)
    {
        x = 10;
    }
    else if(tmpx >= 865 and tmpx < 945)
    {
        x = 11;
    }
    else if(tmpx >= 945 and tmpx < 1025)
    {
        x = 12;
    }
    else if(tmpx >= 1025 and tmpx < 1105)
    {
        x = 13;
    }
    else if(tmpx >= 1105 and tmpx < 1185)
    {
        x = 14;
    }
    else
    {
        return;
    }

    if(tmpy >= 40 and tmpy < 110)
    {
        y = 0;
    }
    else if(tmpy >= 110 and tmpy < 180)
    {
        y = 1;
    }
    else if(tmpy >= 180 and tmpy < 250)
    {
        y = 2;
    }
    else if(tmpy >= 250 and tmpy < 320)
    {
        y = 3;
    }
    else if(tmpy >= 320 and tmpy < 390)
    {
        y = 4;
    }
    else if(tmpy >= 390 and tmpy < 460)
    {
        y = 5;
    }
    else
    {
        return;
    }

    qDebug() << "tmpx : " << tmpx << "  tmpy : " << tmpy;
    qDebug() << "Grid Position: (" << x << ", " << y << ")";  
    addCharacterAtPosition(x, y);
}


void game::addCharacterAtPosition(int x, int y)
{
    Characters *ch = nullptr;

    QJsonObject request;
    request["action"] = "add";

    switch (selectedCharacterType) {
    case TallZombie:
        request["character"] = 1;
        request["x"] = x;
        request["y"] = y;
        break;
    case RegZombie:
        request["character"] = 2;
        request["x"] = x;
        request["y"] = y;
        break;
    case PurpleZombie:
        request["character"] = 3;
        request["x"] = x;
        request["y"] = y;
        break;
    case LeafZombie:
        request["character"] = 4;
        request["x"] = x;
        request["y"] = y;
        break;
    case BucketZombie:
        request["character"] = 5;
        request["x"] = x;
        request["y"] = y;
        break;
    case AstroZombie:
        request["character"] = 6;
        request["x"] = x;
        request["y"] = y;
        break;
    case BoomPlant:
        request["character"] = 7;
        request["x"] = x;
        request["y"] = y;
        break;
    case JalapenoPlant:
        request["character"] = 8;
        request["x"] = x;
        request["y"] = y;
        break;
    case PeashooterPlant:
        request["character"] = 9;
        request["x"] = x;
        request["y"] = y;
        break;
    case TwoPeashooterPlant:
        request["character"] = 10;
        request["x"] = x;
        request["y"] = y;
        break;
    case WalnutPlant:
        request["character"] = 11;
        request["x"] = x;
        request["y"] = y;
        break;
    case PlumMinePlant:
        request["character"] = 12;
        request["x"] = x;
        request["y"] = y;
        break;
    default:
        return;
    }
    qDebug() << request["character"];
    QJsonDocument doc(request);
    QByteArray data = doc.toJson();
    qDebug() << "send data to id :" << ip << " and port " << port;
    socket->write(data);
    socket->flush();

    //scene->addItem(ch);
}

// Slot for button clicks to set the character type
void game::on_tall_Z_Pushbutton_clicked()
{
    selectedCharacterType = TallZombie;
}

// Other slots...
void game::on_Reg_zombie_pushbutton_clicked()
{
    selectedCharacterType = RegZombie;
}

void game::on_purple_pushbutton_clicked()
{
    selectedCharacterType = PurpleZombie;
}

void game::on_leaf_Z_pushbutton_clicked()
{
    selectedCharacterType = LeafZombie;
}

void game::on_bucket_Z_pushbutton_clicked()
{
    selectedCharacterType = BucketZombie;
}

void game::on_astro_Z_pushbutton_clicked()
{
    selectedCharacterType = AstroZombie;
}

void game::on_boom_Pushbutton_clicked()
{
    selectedCharacterType = BoomPlant;
}

void game::on_Jalo_P_button_clicked()
{
    selectedCharacterType = JalapenoPlant;
}

void game::on_peashoot_Pushbutton_clicked()
{
    selectedCharacterType = PeashooterPlant;
}

void game::on_twopeashoot_Pushbutton_clicked()
{
    selectedCharacterType = PeashooterPlant;
}

void game::on_wallnut_Pushbutton_clicked()
{
    selectedCharacterType = WalnutPlant;
}

void game::on_Plum_mine_pushbutton_clicked()
{
    selectedCharacterType = PlumMinePlant;
}
