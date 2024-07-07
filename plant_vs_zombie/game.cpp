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

    // Connect to the server
    connect_to_server(ip, port); // Replace with your server IP and port
}

// Destructor
game::~game()
{
    delete ui;
}

// Slot when connected to the server
void game::onConnected()
{
    qDebug() << "Connected to server";
    QJsonObject request;
    request["action"] = "set_role";
    request["role"] = role;

    QJsonDocument doc(request);
    QByteArray data = doc.toJson();
    socket->write(data);
    socket->flush();
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



// Connect to server
void game::connect_to_server(const QString &ip, int port)
{
    socket->connectToHost(ip, port);
}

// Slot for readyRead signal
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
    if (action == "update") {
        QJsonArray gameState = response["game_state"].toArray();
        updateGameState(gameState);
    } else {
        // Handle other responses as needed
    }
}

// Setter methods
void game::set_ip(QString _ip)
{
    ip = _ip;
}

void game::set_port(int _port) {
    port = _port;
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
    } else {
        // Create a QGraphicsPixmapItem with the background image
        QGraphicsPixmapItem *background = new QGraphicsPixmapItem(backgroundImage);
        background->setPos(0, 0); // Set position at top-left corner of the scene
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
    int x = position.x() / 50; // Assuming each grid cell is 50x50 pixels
    int y = position.y() / 50;

    qDebug() << "Grid Position: (" << x << ", " << y << ")";

    // Now you can use x and y to place your character
    addCharacterAtPosition(x, y);
}


void game::addCharacterAtPosition(int x, int y)
{
    Characters *ch = nullptr;

    switch (selectedCharacterType) {
    case TallZombie:
        ch = new zombies(x, y, 500, 30, "tall", "can move over walnut and move quickly", 1, 1);
        break;
    case RegZombie:
        ch = new zombies(x, y, 500, 25, "regular", "basic zombie with average abilities", 1, 1);
        break;
    case PurpleZombie:
        ch = new zombies(x, y, 4000, 75, "purplehair", "very powerful zombie", 1, 0.5);
        break;
    case LeafZombie:
        ch = new zombies(x, y, 800, 25, "leafhead", "leaves on the head make more resilient", 1, 1);
        break;
    case BucketZombie:
        ch = new zombies(x, y, 1950, 50, "buckethead", "wears a bucket on his head, giving it extra health", 2, 1);
        break;
    case AstroZombie:
        ch = new zombies(x, y, 500, 20, "astronaut", "speeds up after health becomes 100", 1, 1);
        break;
    case BoomPlant:
        ch = new plants(x, y, 200, 30, 1, "boomerang", "all zombies on the same row of the boomerang will lose 15 of their health");
        break;
    case JalapenoPlant:
        ch = new plants(x, y, 0, 0, 300, "jalpeno", "zombies who are in the same row as jalapeno will lose 300 of their health");
        break;
    case PeashooterPlant:
        ch = new plants(x, y, 200, 15, 1, "peashooter", "basic plant that shoots peas at zombies regularly");
        break;
    case TwoPeashooterPlant:
        ch = new plants(x, y, 200, 40, 1, "twopeashooter", "more powerful than basic shooter");
        break;
    case WalnutPlant:
        ch = new plants(x, y, 400, 0, 0, "walnut", "acts as armor and stops zombies");
        break;
    case PlumMinePlant:
        ch = new plants(x, y, 0, 500, 0, "plummine", "those who are in the two squares of the bomb will lose 200 health");
        break;
    default:
        return; // No character selected, do nothing
    }
    scene->addItem(ch);
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
