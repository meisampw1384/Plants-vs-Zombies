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
    qDebug()<<ip<<port;
    socket->connectToHost(ip,port);
    qDebug() << "Connected to server";

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

// Slot for readyRead signal
void game::onReadyRead()
{
    qDebug() << "onReadyRead called";

    QByteArray data = socket->readAll();
    qDebug() << "Data read from socket:" << data;

    QJsonDocument doc = QJsonDocument::fromJson(data);

    if (doc.isNull()) {
        qDebug() << "Failed to parse JSON document from data:" << data;
        return;
    }

    QJsonObject obj_data = doc.object();
    QString action = obj_data["action"].toString();

    if (action == "update") {
        gameState = obj_data["game_state"].toArray();
        qDebug() << "Received update action. Updating game state with:" << gameState;
        updateGameState(gameState);
    } else if (action == "add_char") {
        qDebug() << "Received add_char action. Adding character:" << obj_data["character"];
        Characters *ch = nullptr;
        gameState=obj_data["game_state"].toArray();
        switch (obj_data["character"].toInt()) {
            case 1:
                ch = new zombies(obj_data["x"].toInt(), obj_data["y"].toInt(), 500, 30, "tall", "can move over walnut and move quickly", 1, 1);
                break;
            case 2:
                ch = new zombies(obj_data["x"].toInt(), obj_data["y"].toInt(), 500, 25, "regular", "basic zombie with average abilities", 1, 1);
                break;
            case 3:
                ch = new zombies(obj_data["x"].toInt(), obj_data["y"].toInt(), 4000, 75, "purplehair", "very powerful zombie", 1, 0.5);
                break;
            case 4:
                ch = new zombies(obj_data["x"].toInt(), obj_data["y"].toInt(), 800, 25, "leafhead", "leaves on the head make more resilient", 1, 1);
                break;
            case 5:
                ch = new zombies(obj_data["x"].toInt(), obj_data["y"].toInt(), 1950, 50, "buckethead", "wears a bucket on his head, giving it extra health", 2, 1);
                break;
            case 6:
                ch = new zombies(obj_data["x"].toInt(), obj_data["y"].toInt(), 500, 20, "astronaut", "speeds up after health becomes 100", 1, 1);
                break;
            case 7:
                ch = new plants(obj_data["x"].toInt(), obj_data["y"].toInt(), 200, 30, 1, "boomerang", "all zombies on the same row of the boomerang will lose 15 of their health");
                break;
            case 8:
                ch = new plants(obj_data["x"].toInt(), obj_data["y"].toInt(), 0, 0, 300, "jalpeno", "zombies who are in the same row as jalapeno will lose 300 of their health");
                break;
            case 9:
                ch = new plants(obj_data["x"].toInt(), obj_data["y"].toInt(), 200, 15, 1, "peashooter", "basic plant that shoots peas at zombies regularly");
                break;
            case 10:
                ch = new plants(obj_data["x"].toInt(), obj_data["y"].toInt(), 200, 40, 1, "twopeashooter", "more powerful than basic shooter");
                break;
            case 11:
                ch = new plants(obj_data["x"].toInt(), obj_data["y"].toInt(), 400, 0, 0, "walnut", "acts as armor and stops zombies");
                break;
            case 12:
                ch = new plants(obj_data["x"].toInt(), obj_data["y"].toInt(), 0, 500, 0, "plummine", "those who are in the two squares of the bomb will lose 200 health");
                break;
            default:
                qDebug() << "Unknown character type:" << obj_data["character"];
                return;
        }
        scene->addItem(ch);
    } else {
        qDebug() << "Unsupported action received:" << action;
    }
}





// Process server response


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

//that is update zombies after movement
void game::updateGameState(const QJsonArray &gameState)
{

    QList<QGraphicsItem *> items = scene->items();
    for (QGraphicsItem *item : items) {
        zombies *zombie = dynamic_cast<zombies *>(item);
        if (zombie) {
            scene->removeItem(zombie);
            delete zombie;
        }
    }


    // Iterate through the received game state array
    for (const QJsonValue &value : gameState)
    {
        QJsonObject entity = value.toObject();

        // Determine the type of entity (zombie or plant)
        QString type = entity["type"].toString();
        if (type == "zombie") {
            QString subtype = entity["subtype"].toString();
            int x = entity["x"].toInt();
            int y = entity["y"].toInt();

            // Create a new zombie object based on subtype
            Characters *ch = nullptr;
            if (subtype == "tall") {
                ch = new zombies(x, y, entity["health"].toInt(), entity["damage"].toInt(), "tall", entity["discription"].toString(),entity["move_delay"].toDouble() ,entity["time_between"].toDouble());
            } else if (subtype == "regular") {
                ch = new zombies(x, y, entity["health"].toInt(), entity["damage"].toInt(), "regular", entity["discription"].toString(),entity["move_delay"].toDouble() , entity["time_between"].toDouble());
            } else if (subtype == "purplehair") {
                ch = new zombies(x, y, entity["health"].toInt(), entity["damage"].toInt(), "purplehair", entity["discription"].toString(),entity["move_delay"].toDouble() , entity["time_between"].toDouble());
            } else if (subtype == "leafhead") {
                ch = new zombies(x, y, entity["health"].toInt(), entity["damage"].toInt(), "leafhead", entity["discription"].toString(),entity["move_delay"].toDouble() , entity["time_between"].toDouble());
            } else if (subtype == "buckethead") {
                ch = new zombies(x, y, entity["health"].toInt(), entity["damage"].toInt(), "buckethead", entity["discription"].toString(),entity["move_delay"].toDouble() , entity["time_between"].toDouble());
            } else if (subtype == "astronaut") {
                ch = new zombies(x, y, entity["health"].toInt(), entity["damage"].toInt(), "astronaut", entity["discription"].toString(), entity["move_delay"].toDouble() ,entity["time_between"].toDouble());
            }

            // Add the zombie to the scene
            if (ch) {
                scene->addItem(ch);
            }
        } else if (type == "plant") {
            QString subtype = entity["subtype"].toString();
            int x = entity["x"].toInt();
            int y = entity["y"].toInt();

            // Create a new plant object based on subtype
            Characters *plant = nullptr;
            if (subtype == "boomerang") {
                plant = new plants(x, y, entity["health"].toInt(), entity["damage"].toInt(), entity["firing_rate"].toInt(), "boomerang", entity["discription"].toString());
            } else if (subtype == "jalpeno") {
                plant = new plants(x, y, entity["health"].toInt(), entity["damage"].toInt(), entity["firing_rate"].toInt(), "jalpeno", entity["discription"].toString());
            } else if (subtype == "peashooter") {
                plant = new plants(x, y, entity["health"].toInt(), entity["damage"].toInt(), entity["firing_rate"].toInt(), "peashooter", entity["discription"].toString());
            } else if (subtype == "twopeashooter") {
                plant = new plants(x, y, entity["health"].toInt(), entity["damage"].toInt(), entity["firing_rate"].toInt(), "twopeashooter", entity["discription"].toString());
            } else if (subtype == "walnut") {
                plant = new plants(x, y, entity["health"].toInt(), entity["damage"].toInt(), entity["firing_rate"].toInt(), "walnut", entity["discription"].toString());
            } else if (subtype == "plummine") {
                plant = new plants(x, y, entity["health"].toInt(), entity["damage"].toInt(), entity["firing_rate"].toInt(), "plummine", entity["discription"].toString());
            }

            // Add the plant to the scene
            if (plant) {
                scene->addItem(plant);
            }

        }
        else if (type=="sun"){
            int x= entity["x"].toInt();
            int y= entity["y"].toInt();
            QPixmap sun ("../images/sun.png");
            QGraphicsPixmapItem *sunG=new QGraphicsPixmapItem(sun);
            sunG->setPos(x*77,y*72);
            sunG->setScale(.06);
            sunG->setData(Qt::UserRole, "sun");
            scene->addItem(sunG);
            connect(scene, &CustomGraphicsScene::sunClicked, this, &game::onSunClicked);


        }
        else if (type=="brain"){
            int x= entity["x"].toInt();
            int y= entity["y"].toInt();
            QPixmap brain ("../images/Brain.png");
            QGraphicsPixmapItem *brainG=new QGraphicsPixmapItem(brain);
            brainG->setPos(x*77,y*72);
            brainG->setScale(.2);
            brainG->setData(Qt::UserRole, "brain");
            scene->addItem(brainG);
            connect(scene, &CustomGraphicsScene::brainClicked, this, &game::onBrainClicked);


        }
        else {
            qDebug() << "Unsupported entity type received:" << type;
        }
    }
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

void game::onBrainClicked(const QPointF &pos)
{
    qDebug() << "Brain clicked at position:" << pos;

       // Example: Remove brain item from the scene
    QList<QGraphicsItem *> items = scene->items(pos);
    for (QGraphicsItem *item : items) {
        if (item->data(Qt::UserRole) == "brain") {
            scene->removeItem(item);
            delete item;
            break; // Assuming there's only one brain item at this position
        }
    }

    QString x=ui->amount_of_brain->text();
    QString currentText = ui->amount_of_brain->text();
    int currentAmount = currentText.toInt();
    currentAmount += 25;
    ui->amount_of_brain->setText(QString::number(currentAmount));


    QJsonObject request;
    request["action"] = "delete";
    request["type"] = "brain";
    request["x"] = static_cast<int>(pos.x() / 77);  // Convert to grid coordinates if necessary
    request["y"] = static_cast<int>(pos.y() / 72);

    QJsonDocument doc(request);
    QByteArray requestData = doc.toJson();

    socket->write(requestData);
    socket->flush();
}

void game::onSunClicked(const QPointF &pos)
{
    // Handle sun clicked event here
    qDebug() << "Sun clicked at position:" << pos;

    // Example: Remove sun item from the scene
    QList<QGraphicsItem *> items = scene->items(pos);
    for (QGraphicsItem *item : items) {
        if (item->data(Qt::UserRole) == "sun") {
            scene->removeItem(item);

            // Update the amount of sun in the UI

            delete item;
            break; // Assuming there's only one sun item at this position
        }
    }
    QString currentText = ui->amoun_of_sun->text();
    int currentAmount = currentText.toInt();
    currentAmount += 25;
    ui->amoun_of_sun->setText(QString::number(currentAmount));

    QJsonObject request;
    request["action"] = "delete";
    request["type"] = "sun";
    request["x"] = static_cast<int>(pos.x() / 77);  // Convert to grid coordinates if necessary
    request["y"] = static_cast<int>(pos.y() / 72);

    QJsonDocument doc(request);
    QByteArray requestData = doc.toJson();

    socket->write(requestData);
    socket->flush();
}




void game::addCharacterAtPosition(int x, int y)
{

    QJsonObject newEntity;
    static int entityIdCounter = 2; // Start from 2 since 1 is already used for initial entities

    QJsonObject request;
    request["action"] = "add";

    switch (selectedCharacterType) {
        case TallZombie:

            newEntity["type"] = "zombie";
            newEntity["subtype"] = "tall";
            newEntity["health"] = 500;
            newEntity["damage"] = 30;
            newEntity["move_delay"] = 1000; // Example delay
            newEntity["time_between"] = 1000;
            newEntity["last_move"] = QDateTime::currentMSecsSinceEpoch();
            newEntity["description"] = "can move over walnut and move quickly";
            request["character"] = 1;
            break;
        case RegZombie:

            newEntity["type"] = "zombie";
            newEntity["subtype"] = "regular";
            newEntity["health"] = 500;
            newEntity["damage"] = 25;
            newEntity["move_delay"] = 1000;
            newEntity["time_between"] = 1000;
            newEntity["last_move"] = QDateTime::currentMSecsSinceEpoch();
            newEntity["description"] = "basic zombie with average abilities";
            request["character"] = 2;
            break;
        case PurpleZombie:

            newEntity["type"] = "zombie";
            newEntity["subtype"] = "purplehair";
            newEntity["health"] = 4000;
            newEntity["damage"] = 75;
            newEntity["move_delay"] = 1000;
            newEntity["time_between"] = 500;
            newEntity["last_move"] = QDateTime::currentMSecsSinceEpoch();
            newEntity["description"] = "very powerful zombie";
            request["character"] = 3;
            break;
        case LeafZombie:

            newEntity["type"] = "zombie";
            newEntity["subtype"] = "leafhead";
            newEntity["health"] = 800;
            newEntity["damage"] = 25;
            newEntity["move_delay"] = 1000; // Example delay
            newEntity["time_between"] = 500;
            newEntity["last_move"] = QDateTime::currentMSecsSinceEpoch();
            newEntity["description"] = "leaves on the head make more resilient";
            request["character"] = 4;
            break;
        case BucketZombie:

            newEntity["type"] = "zombie";
            newEntity["subtype"] = "buckethead";
            newEntity["health"] = 1950;
            newEntity["damage"] = 50;
            newEntity["move_delay"] = 2000; // Example delay
            newEntity["time_between"] = 1000;
            newEntity["last_move"] = QDateTime::currentMSecsSinceEpoch();
            newEntity["description"] = "wears a bucket on his head, giving it extra health";
            request["character"] = 5;
            break;
        case AstroZombie:

            newEntity["type"] = "zombie";
            newEntity["subtype"] = "astronaut";
            newEntity["health"] = 500;
            newEntity["damage"] = 20;
            newEntity["move_delay"] = 1000; // Example delay
            newEntity["time_between"] = 1000;
            newEntity["last_move"] = QDateTime::currentMSecsSinceEpoch();
            newEntity["description"] = "speeds up after health becomes 100";
            request["character"] = 6;
            break;
        case BoomPlant:
            newEntity["type"] = "plant";
            newEntity["subtype"] = "boomerang";
            newEntity["health"] = 200;
            newEntity["damage"] = 30;
            newEntity["description"] = "all zombies on the same row of the boomerang will lose 15 of their health";
            request["character"] = 7;
            break;
        case JalapenoPlant:
            newEntity["type"] = "plant";
            newEntity["subtype"] = "jalpeno";
            newEntity["health"] = 0;
            newEntity["damage"] = 300;
            newEntity["firing_rate"] = 0;
            newEntity["description"] = "zombies who are in the same row as jalapeno will lose 300 of their health";
            request["character"] = 8;
            break;
        case PeashooterPlant:

            newEntity["type"] = "plant";
            newEntity["subtype"] = "peashooter";
            newEntity["health"] = 200;
            newEntity["damage"] = 15;
            newEntity["firing_rate"] = 1;
            newEntity["description"] = "basic plant that shoots peas at zombies regularly";
            request["character"] = 9;
            break;
        case TwoPeashooterPlant:

            newEntity["type"] = "plant";
            newEntity["subtype"] = "twopeashooter";
            newEntity["health"] = 200;
            newEntity["damage"] = 40;
            newEntity["firing_rate"] = 1;
            newEntity["description"] = "more powerful than basic shooter";
            request["character"] = 10;
            break;
        case WalnutPlant:

            newEntity["type"] = "plant";
            newEntity["subtype"] = "walnut";
            newEntity["health"] = 400;
            newEntity["damage"] = 0;
            newEntity["firing_rate"] = 0;
            newEntity["description"] = "acts as armor and stops zombies";
            request["character"] = 11;
            break;
        case PlumMinePlant:

            newEntity["type"] = "plant";
            newEntity["subtype"] = "plummine";
            newEntity["health"] = 0;
            newEntity["damage"] = 500;
            newEntity["firing_rate"] = 0;
            newEntity["description"] = "those who are in the two squares of the bomb will lose 200 health";
            request["character"] = 12;
            break;
        default:
            return;
    }

    // Set common properties
    newEntity["id"] = entityIdCounter++;
    newEntity["x"] = x;
    newEntity["y"] = y;



    // Send the new game state to the server
    request["entity"] = newEntity;
    request["x"]=x;
    request["y"]=y;

    QJsonDocument doc(request);
    QByteArray data = doc.toJson();
    socket->write(data);
    socket->flush();

    qDebug() << request["character"];
    qDebug() << "send data to id :" << ip << " and port " << port;
    socket->write(data);
    socket->flush();
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
    selectedCharacterType = TwoPeashooterPlant;
}

void game::on_wallnut_Pushbutton_clicked()
{
    selectedCharacterType = WalnutPlant;
}

void game::on_Plum_mine_pushbutton_clicked()
{
    selectedCharacterType = PlumMinePlant;
}
