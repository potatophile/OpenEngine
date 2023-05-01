#include "Engine/Game.h"
#include "Engine/Graphics/Model.h"
#include "Engine/Graphics/GraphicsEngine.h"
#include "Engine/Input.h"
#include "Engine/Graphics/Camera.h"
#include "Engine/Graphics/Material.h"
#include "Engine/Collision/Collision.h"

Game& Game::GetGameInstance()
{
    static Game* GameInstance = new Game();
    return *GameInstance;
}

void Game::DestroyGameInstance()
{
    static Game* GameInstance = &GetGameInstance();

    delete GameInstance;
}

TexturePtr Game::GetDefaultEngineTexture()
{
    return Graphics->DefaultEngineTexture;
}

MaterialPtr Game::GetDefaultEngineMaterial()
{
    return Graphics->DefaultEngineMaterial;
}

void Game::RemoveModelFromGame(ModelPtr& ModelToRemove)
{
    //remove from the graphics engine
    Graphics->RemoveModel(ModelToRemove);

    //change the reference to nullptr and rmeove from the game
    ModelToRemove = nullptr;
}

Game::Game()
{
    cout << "Game Initialized" << endl;

    Graphics = nullptr;
    bIsGameOver = false;
}

Game::~Game()
{
    //since nothing else is storing the graphics in memory
    //this will destroy the graphics from the memory
    Graphics = nullptr;

    cout << "Game Over..." << endl;
}

void Game::Start(const char* WTitle, bool bFullscreen, int WWidth, int WHeight)
{
    //Load the window using graphics class
    Graphics = make_shared<GraphicsEngine>();

    //if the window fails to load then bIsGameOver = true
    if (!Graphics->InitGE(WTitle, bFullscreen, WWidth, WHeight)) {
        bIsGameOver = true;
    }

    Run();
}

void Game::Run()
{
    if (!bIsGameOver) {
        //create an input object to detect input
        GameInput = new Input();

        //create a shader
        ShaderPtr TextureShader = Graphics->CreateShader({
            L"Game/Shader/TextureShader/TextureShader.svert",
            L"Game/Shader/TextureShader/TextureShader.sfrag"
            });
        
        //import custom meshes
        Ground = Graphics->ImportModel("Game/Models/Primitives/Cube.fbx", TextureShader);

        /*"Coin" (https://skfb.ly/oyyrJ) by quomitter is licensed under Creative Commons Attribution (http://creativecommons.org/licenses/by/4.0/).*/
        Coin1 = Graphics->ImportModel("Game/Models/Pickup/Coin.fbx", TextureShader);
        Coin2 = Graphics->ImportModel("Game/Models/Pickup/Coin.fbx", TextureShader);
        Coin3 = Graphics->ImportModel("Game/Models/Pickup/Coin.fbx", TextureShader);
        Coin4 = Graphics->ImportModel("Game/Models/Pickup/Coin.fbx", TextureShader);
        Coin5 = Graphics->ImportModel("Game/Models/Pickup/Coin.fbx", TextureShader);
        Coin6 = Graphics->ImportModel("Game/Models/Pickup/Coin.fbx", TextureShader);
        Coin7 = Graphics->ImportModel("Game/Models/Pickup/Coin.fbx", TextureShader);
        Coin8 = Graphics->ImportModel("Game/Models/Pickup/Coin.fbx", TextureShader);
        Coin9 = Graphics->ImportModel("Game/Models/Pickup/Coin.fbx", TextureShader);
        Coin10 = Graphics->ImportModel("Game/Models/Pickup/Coin.fbx", TextureShader);
        Coin11 = Graphics->ImportModel("Game/Models/Pickup/Coin.fbx", TextureShader);
        Coin12 = Graphics->ImportModel("Game/Models/Pickup/Coin.fbx", TextureShader);
        Coin13 = Graphics->ImportModel("Game/Models/Pickup/Coin.fbx", TextureShader);
        Coin14 = Graphics->ImportModel("Game/Models/Pickup/Coin.fbx", TextureShader);
        Coin15 = Graphics->ImportModel("Game/Models/Pickup/Coin.fbx", TextureShader);
        Coin16 = Graphics->ImportModel("Game/Models/Pickup/Coin.fbx", TextureShader);
        Coin17 = Graphics->ImportModel("Game/Models/Pickup/Coin.fbx", TextureShader);
        Coin18 = Graphics->ImportModel("Game/Models/Pickup/Coin.fbx", TextureShader);

        /*Trockk 2022, Genesis 451 - Download Free 3D model by Trockk (@Timrockk),
        sketchfab.com, viewed 19 March 2023, <https://sketchfab.com/3d-models/genesis-451-3326d51402f74afcae45ef16f59ac0e1>*/
        Spike1 = Graphics->ImportModel("Game/Models/Spike/source/Spike.fbx", TextureShader);
        Spike2 = Graphics->ImportModel("Game/Models/Spike/source/Spike.fbx", TextureShader);
        Spike3 = Graphics->ImportModel("Game/Models/Spike/source/Spike.fbx", TextureShader);
        Spike4 = Graphics->ImportModel("Game/Models/Spike/source/Spike.fbx", TextureShader);
        Spike5 = Graphics->ImportModel("Game/Models/Spike/source/Spike.fbx", TextureShader);
        Spike6 = Graphics->ImportModel("Game/Models/Spike/source/Spike.fbx", TextureShader);
        Spike7 = Graphics->ImportModel("Game/Models/Spike/source/Spike.fbx", TextureShader);
        Spike8 = Graphics->ImportModel("Game/Models/Spike/source/Spike.fbx", TextureShader);
        Spike9 = Graphics->ImportModel("Game/Models/Spike/source/Spike.fbx", TextureShader);
        Spike10 = Graphics->ImportModel("Game/Models/Spike/source/Spike.fbx", TextureShader);
        Spike11 = Graphics->ImportModel("Game/Models/Spike/source/Spike.fbx", TextureShader);
        Spike12 = Graphics->ImportModel("Game/Models/Spike/source/Spike.fbx", TextureShader);
        Spike13 = Graphics->ImportModel("Game/Models/Spike/source/Spike.fbx", TextureShader);
        Spike14 = Graphics->ImportModel("Game/Models/Spike/source/Spike.fbx", TextureShader);
        
        /*"Fallout Car 2" (https://skfb.ly/RySz) by Renafox is licensed under Creative Commons Attribution-NonCommercial (http://creativecommons.org/licenses/by-nc/4.0/).*/
        Car = Graphics->ImportModel("Game/Models/fallout-car/source/car_low.fbx", TextureShader);
        
        /*"Road Barrier" (https://skfb.ly/6s9IX) by Daniyal Malik is licensed under Creative Commons Attribution (http://creativecommons.org/licenses/by/4.0/).*/
        LWall1 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        RWall1 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        LWall2 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        RWall2 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        LWall3 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        RWall3 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        LWall4 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        RWall4 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        LWall5 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        RWall5 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        RWall6 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        LWall6 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        RWall7 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        LWall7 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        RWall8 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        LWall8 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        LWall9 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        RWall9 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        LWall10 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        RWall10 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        LWall11 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        RWall11 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        LWall12 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        RWall12 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        LWall13 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        RWall13 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        LWall14 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        RWall14 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        LWall15 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        RWall15 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        LWall16 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        RWall16 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        LWall17 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        RWall17 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        LWall18 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        RWall18 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        LWall19 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        RWall19 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        LWall20 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        RWall20 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        LWall21 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        RWall21 = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        StartWall = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        EndWall = Graphics->ImportModel("Game/Models/road-barrier/source/barrier.obj", TextureShader);
        
        //Create textures and materials for models
        if (Ground != nullptr) {
            //initial transformations for the meshes
            Ground->Transform.Location = Vector3(150.0f, -3.5f, 3.0f);
            Ground->Transform.Scale = Vector3(300.0f, 1.0f, 40.0f);
            Ground->Transform.Rotation.x = 180.0f;

            //Road Texture: https://www.cgbookcase.com/textures/highway-road-clean-01
            TexturePtr TRoad = Graphics->CreateTexture("Game/Textures/HighwayRoadClean01_1K_BaseColorTest2.png");
            MaterialPtr MRoad = make_shared<Material>();
            MRoad->BaseColour.TextureV3 = TRoad;

            Ground->SetMaterialBySlot(0, MRoad);

            //adding collision to ground
            Ground->AddCollisionToModel(Vector3(300.1f, 1.1f, 40.1f));
        }
        
        if (Coin1 != nullptr) {
             //coin1
            //transform coin model
            Coin1->Transform.Scale = Vector3(0.005f);
            Coin1->Transform.Rotation.x = 90.0f;
            Coin1->Transform.Location = Vector3(20.0f, -1.5f, -7.0f);

            //create texture for coin
            TexturePtr TCoin = Graphics->CreateTexture("Game/Models/Pickup/Gold.png");

            //create material
            MaterialPtr MCoin = make_shared<Material>();
            MCoin->BaseColour.TextureV3 = TCoin;

            //apply the material
            Coin1->SetMaterialBySlot(0, MCoin);

            //adding collision to coin
            Coin1->AddCollisionToModel(Vector3(1.0f, 1.0f, 1.0f));
        }
        if (Coin2 != nullptr) {
            //coin2
           //transform coin model
            Coin2->Transform.Scale = Vector3(0.005f);
            Coin2->Transform.Rotation.x = 90.0f;
            Coin2->Transform.Location = Vector3(30.0f, -1.5f, -9.0f);

            //create texture for coin
            TexturePtr TCoin = Graphics->CreateTexture("Game/Models/Pickup/Gold.png");

            //create material
            MaterialPtr MCoin = make_shared<Material>();
            MCoin->BaseColour.TextureV3 = TCoin;

            //apply the material
            Coin2->SetMaterialBySlot(0, MCoin);

            //adding collision to coin
            Coin2->AddCollisionToModel(Vector3(1.0f, 1.0f, 1.0f));
        }
        if (Coin3 != nullptr) {
            //coin3
           //transform coin model
            Coin3->Transform.Scale = Vector3(0.005f);
            Coin3->Transform.Rotation.x = 90.0f;
            Coin3->Transform.Location = Vector3(30.0f, -1.5f, 13.0f);

            //create texture for coin
            TexturePtr TCoin = Graphics->CreateTexture("Game/Models/Pickup/Gold.png");

            //create material
            MaterialPtr MCoin = make_shared<Material>();
            MCoin->BaseColour.TextureV3 = TCoin;

            //apply the material
            Coin3->SetMaterialBySlot(0, MCoin);

            //adding collision to coin
            Coin3->AddCollisionToModel(Vector3(1.0f, 1.0f, 1.0f));
        }
        if (Coin4 != nullptr) {
            //coin4
           //transform coin model
            Coin4->Transform.Scale = Vector3(0.005f);
            Coin4->Transform.Rotation.x = 90.0f;
            Coin4->Transform.Location = Vector3(40.0f, -1.5f, 7.0f);

            //create texture for coin
            TexturePtr TCoin = Graphics->CreateTexture("Game/Models/Pickup/Gold.png");

            //create material
            MaterialPtr MCoin = make_shared<Material>();
            MCoin->BaseColour.TextureV3 = TCoin;

            //apply the material
            Coin4->SetMaterialBySlot(0, MCoin);

            //adding collision to coin
            Coin4->AddCollisionToModel(Vector3(1.0f, 1.0f, 1.0f));
        }
        if (Coin5 != nullptr) {
            //coin 5
           //transform coin model
            Coin5->Transform.Scale = Vector3(0.005f);
            Coin5->Transform.Rotation.x = 90.0f;
            Coin5->Transform.Location = Vector3(50.0f, -1.5f, 6.0f);

            //create texture for coin
            TexturePtr TCoin = Graphics->CreateTexture("Game/Models/Pickup/Gold.png");

            //create material
            MaterialPtr MCoin = make_shared<Material>();
            MCoin->BaseColour.TextureV3 = TCoin;

            //apply the material
            Coin5->SetMaterialBySlot(0, MCoin);

            //adding collision to coin
            Coin5->AddCollisionToModel(Vector3(1.0f, 1.0f, 1.0f));
        }
        if (Coin6 != nullptr) {
            //coin6
           //transform coin model
            Coin6->Transform.Scale = Vector3(0.005f);
            Coin6->Transform.Rotation.x = 90.0f;
            Coin6->Transform.Location = Vector3(60.0f, -1.5f, -2.0f);

            //create texture for coin
            TexturePtr TCoin = Graphics->CreateTexture("Game/Models/Pickup/Gold.png");

            //create material
            MaterialPtr MCoin = make_shared<Material>();
            MCoin->BaseColour.TextureV3 = TCoin;

            //apply the material
            Coin6->SetMaterialBySlot(0, MCoin);

            //adding collision to coin
            Coin6->AddCollisionToModel(Vector3(1.0f, 1.0f, 1.0f));
        }
        if (Coin7 != nullptr) {
            //coin 7
           //transform coin model
            Coin7->Transform.Scale = Vector3(0.005f);
            Coin7->Transform.Rotation.x = 90.0f;
            Coin7->Transform.Location = Vector3(70.0f, -1.5f, -1.0f);

            //create texture for coin
            TexturePtr TCoin = Graphics->CreateTexture("Game/Models/Pickup/Gold.png");

            //create material
            MaterialPtr MCoin = make_shared<Material>();
            MCoin->BaseColour.TextureV3 = TCoin;

            //apply the material
            Coin7->SetMaterialBySlot(0, MCoin);

            //adding collision to coin
            Coin7->AddCollisionToModel(Vector3(1.0f, 1.0f, 1.0f));
        }
        if (Coin8 != nullptr) {
            //coin8
           //transform coin model
            Coin8->Transform.Scale = Vector3(0.005f);
            Coin8->Transform.Rotation.x = 90.0f;
            Coin8->Transform.Location = Vector3(80.0f, -1.5f, 7.0f);

            //create texture for coin
            TexturePtr TCoin = Graphics->CreateTexture("Game/Models/Pickup/Gold.png");

            //create material
            MaterialPtr MCoin = make_shared<Material>();
            MCoin->BaseColour.TextureV3 = TCoin;

            //apply the material
            Coin8->SetMaterialBySlot(0, MCoin);

            //adding collision to coin
            Coin8->AddCollisionToModel(Vector3(1.0f, 1.0f, 1.0f));
        }
        if (Coin9 != nullptr) {
            //coin9
           //transform coin model
            Coin9->Transform.Scale = Vector3(0.005f);
            Coin9->Transform.Rotation.x = 90.0f;
            Coin9->Transform.Location = Vector3(90.0f, -1.5f, 9.0f);
            
            //create texture for coin
            TexturePtr TCoin = Graphics->CreateTexture("Game/Models/Pickup/Gold.png");

            //create material
            MaterialPtr MCoin = make_shared<Material>();
            MCoin->BaseColour.TextureV3 = TCoin;

            //apply the material
            Coin9->SetMaterialBySlot(0, MCoin);

            //adding collision to coin
            Coin9->AddCollisionToModel(Vector3(1.0f, 1.0f, 1.0f));
        }
        if (Coin10 != nullptr) {
            //coin10
           //transform coin model
            Coin10->Transform.Scale = Vector3(0.005f);
            Coin10->Transform.Rotation.x = 90.0f;
            Coin10->Transform.Location = Vector3(110.0f, -1.5f, 8.0f);
            
            //create texture for coin
            TexturePtr TCoin = Graphics->CreateTexture("Game/Models/Pickup/Gold.png");

            //create material
            MaterialPtr MCoin = make_shared<Material>();
            MCoin->BaseColour.TextureV3 = TCoin;

            //apply the material
            Coin10->SetMaterialBySlot(0, MCoin);

            //adding collision to coin
            Coin10->AddCollisionToModel(Vector3(1.0f, 1.0f, 1.0f));
        }
        if (Coin11 != nullptr) {
            //coin11
           //transform coin model
            Coin11->Transform.Scale = Vector3(0.005f);
            Coin11->Transform.Rotation.x = 90.0f;
            Coin11->Transform.Location = Vector3(120.0f, -1.5f, 7.0f);
            
            //create texture for coin
            TexturePtr TCoin = Graphics->CreateTexture("Game/Models/Pickup/Gold.png");

            //create material
            MaterialPtr MCoin = make_shared<Material>();
            MCoin->BaseColour.TextureV3 = TCoin;

            //apply the material
            Coin11->SetMaterialBySlot(0, MCoin);

            //adding collision to coin
            Coin11->AddCollisionToModel(Vector3(1.0f, 1.0f, 1.0f));
        }
        if (Coin12 != nullptr) {
            //coin12
           //transform coin model
            Coin12->Transform.Scale = Vector3(0.005f);
            Coin12->Transform.Rotation.x = 90.0f;
            Coin12->Transform.Location = Vector3(140.0f, -1.5f, 2.0f);

            //create texture for coin
            TexturePtr TCoin = Graphics->CreateTexture("Game/Models/Pickup/Gold.png");

            //create material
            MaterialPtr MCoin = make_shared<Material>();
            MCoin->BaseColour.TextureV3 = TCoin;

            //apply the material
            Coin12->SetMaterialBySlot(0, MCoin);

            //adding collision to coin
            Coin12->AddCollisionToModel(Vector3(1.0f, 1.0f, 1.0f));
        }
        if (Coin13 != nullptr) {
            //coin13
           //transform coin model
            Coin13->Transform.Scale = Vector3(0.005f);
            Coin13->Transform.Rotation.x = 90.0f;
            Coin13->Transform.Location = Vector3(150.0f, -1.5f, 7.0f);
            
            //create texture for coin
            TexturePtr TCoin = Graphics->CreateTexture("Game/Models/Pickup/Gold.png");

            //create material
            MaterialPtr MCoin = make_shared<Material>();
            MCoin->BaseColour.TextureV3 = TCoin;

            //apply the material
            Coin13->SetMaterialBySlot(0, MCoin);

            //adding collision to coin
            Coin13->AddCollisionToModel(Vector3(1.0f, 1.0f, 1.0f));
        }
        if (Coin14 != nullptr) {
            //coin14
           //transform coin model
            Coin14->Transform.Scale = Vector3(0.005f);
            Coin14->Transform.Rotation.x = 90.0f;
            Coin14->Transform.Location = Vector3(170.0f, -1.5f, 4.0f);
            
            //create texture for coin
            TexturePtr TCoin = Graphics->CreateTexture("Game/Models/Pickup/Gold.png");

            //create material
            MaterialPtr MCoin = make_shared<Material>();
            MCoin->BaseColour.TextureV3 = TCoin;

            //apply the material
            Coin14->SetMaterialBySlot(0, MCoin);

            //adding collision to coin
            Coin14->AddCollisionToModel(Vector3(1.0f, 1.0f, 1.0f));
        }
        if (Coin15 != nullptr) {
            //coin1
           //transform coin model
            Coin15->Transform.Scale = Vector3(0.005f);
            Coin15->Transform.Rotation.x = 90.0f;
            Coin15->Transform.Location = Vector3(190.0f, -1.5f, -2.0f);
            
            //create texture for coin
            TexturePtr TCoin = Graphics->CreateTexture("Game/Models/Pickup/Gold.png");

            //create material
            MaterialPtr MCoin = make_shared<Material>();
            MCoin->BaseColour.TextureV3 = TCoin;

            //apply the material
            Coin15->SetMaterialBySlot(0, MCoin);

            //adding collision to coin
            Coin15->AddCollisionToModel(Vector3(1.0f, 1.0f, 1.0f));
        }
        if (Coin16 != nullptr) {
            //coin16
           //transform coin model
            Coin16->Transform.Scale = Vector3(0.005f);
            Coin16->Transform.Rotation.x = 90.0f;
            Coin16->Transform.Location = Vector3(220.0f, -1.5f, -2.0f);
            
            //create texture for coin
            TexturePtr TCoin = Graphics->CreateTexture("Game/Models/Pickup/Gold.png");

            //create material
            MaterialPtr MCoin = make_shared<Material>();
            MCoin->BaseColour.TextureV3 = TCoin;

            //apply the material
            Coin16->SetMaterialBySlot(0, MCoin);

            //adding collision to coin
            Coin16->AddCollisionToModel(Vector3(1.0f, 1.0f, 1.0f));
        }
        if (Coin17 != nullptr) {
            //coin17
           //transform coin model
            Coin17->Transform.Scale = Vector3(0.005f);
            Coin17->Transform.Rotation.x = 90.0f;
            Coin17->Transform.Location = Vector3(250.0f, -1.5f, -2.0f);
            
            //create texture for coin
            TexturePtr TCoin = Graphics->CreateTexture("Game/Models/Pickup/Gold.png");

            //create material
            MaterialPtr MCoin = make_shared<Material>();
            MCoin->BaseColour.TextureV3 = TCoin;

            //apply the material
            Coin17->SetMaterialBySlot(0, MCoin);

            //adding collision to coin
            Coin17->AddCollisionToModel(Vector3(1.0f, 1.0f, 1.0f));
        }
        if (Coin18 != nullptr) {
            //coin18
           //transform coin model
            Coin18->Transform.Scale = Vector3(0.005f);
            Coin18->Transform.Rotation.x = 90.0f;
            Coin18->Transform.Location = Vector3(190.0f, -1.5f, 8.0f);

            //create texture for coin
            TexturePtr TCoin = Graphics->CreateTexture("Game/Models/Pickup/Gold.png");

            //create material
            MaterialPtr MCoin = make_shared<Material>();
            MCoin->BaseColour.TextureV3 = TCoin;

            //apply the material
            Coin18->SetMaterialBySlot(0, MCoin);

            //adding collision to coin
            Coin18->AddCollisionToModel(Vector3(1.0f, 1.0f, 1.0f));
        }

        if (Spike1 != nullptr) {
            //transform spike1 model
            Spike1->Transform.Scale = Vector3(0.00009f);
            Spike1->Transform.Rotation.x = 90.0f;
            Spike1->Transform.Location = Vector3(25.0f, -2.5f, 0.5f);
            //create texture for spike
            TexturePtr TSpike = Graphics->CreateTexture("Game/Models/Spike/Spike.png");

            //create material
            MaterialPtr MSpike = make_shared<Material>();
            MSpike->BaseColour.TextureV3 = TSpike;

            //apply the material
            Spike1->SetMaterialBySlot(0, MSpike);

            //adding collision to spike
            Spike1->AddCollisionToModel(Vector3(1.0f, 1.0f, 1.0f));
        }
        if (Spike2 != nullptr) {
            //transform spike 2 model
            Spike2->Transform.Scale = Vector3(0.00009f);
            Spike2->Transform.Rotation.x = 90.0f;
            Spike2->Transform.Location = Vector3(35.0f, -2.5f, -1.0f);

            //create texture for spike
            TexturePtr TSpike = Graphics->CreateTexture("Game/Models/Spike/Spike.png");

            //create material
            MaterialPtr MSpike = make_shared<Material>();
            MSpike->BaseColour.TextureV3 = TSpike;

            //apply the material
            Spike2->SetMaterialBySlot(0, MSpike);

            //adding collision to spike
            Spike2->AddCollisionToModel(Vector3(1.0f, 1.0f, 1.0f));
        }
        if (Spike3 != nullptr) {
            //transform spike 3 model
            Spike3->Transform.Scale = Vector3(0.00009f);
            Spike3->Transform.Rotation.x = 90.0f;
            Spike3->Transform.Location = Vector3(35.0f, -2.5f, 13.0f);

            //create texture for spike
            TexturePtr TSpike = Graphics->CreateTexture("Game/Models/Spike/Spike.png");

            //create material
            MaterialPtr MSpike = make_shared<Material>();
            MSpike->BaseColour.TextureV3 = TSpike;

            //apply the material
            Spike3->SetMaterialBySlot(0, MSpike);

            //adding collision to spike
            Spike3->AddCollisionToModel(Vector3(1.0f, 1.0f, 1.0f));
        }
        if (Spike4 != nullptr) {
            //transform spike 4 model
            Spike4->Transform.Scale = Vector3(0.00009f);
            Spike4->Transform.Rotation.x = 90.0f;
            Spike4->Transform.Location = Vector3(45.0f, -2.5f, 0.0f);

            //create texture for spike
            TexturePtr TSpike = Graphics->CreateTexture("Game/Models/Spike/Spike.png");

            //create material
            MaterialPtr MSpike = make_shared<Material>();
            MSpike->BaseColour.TextureV3 = TSpike;

            //apply the material
            Spike4->SetMaterialBySlot(0, MSpike);

            //adding collision to spike
            Spike4->AddCollisionToModel(Vector3(1.0f, 1.0f, 1.0f));
        }
        if (Spike5 != nullptr) {
            //transform spike 5 model
            Spike5->Transform.Scale = Vector3(0.00009f);
            Spike5->Transform.Rotation.x = 90.0f;
            Spike5->Transform.Location = Vector3(60.0f, -2.5f, -10.0f);

            //create texture for spike
            TexturePtr TSpike = Graphics->CreateTexture("Game/Models/Spike/Spike.png");

            //create material
            MaterialPtr MSpike = make_shared<Material>();
            MSpike->BaseColour.TextureV3 = TSpike;

            //apply the material
            Spike5->SetMaterialBySlot(0, MSpike);

            //adding collision to spike
            Spike5->AddCollisionToModel(Vector3(1.0f, 1.0f, 1.0f));
        }
        if (Spike6 != nullptr) {
            //transform spike 6 model
            Spike6->Transform.Scale = Vector3(0.00009f);
            Spike6->Transform.Rotation.x = 90.0f;
            Spike6->Transform.Location = Vector3(80.0f, -2.5f, -8.0f);

            //create texture for spike
            TexturePtr TSpike = Graphics->CreateTexture("Game/Models/Spike/Spike.png");

            //create material
            MaterialPtr MSpike = make_shared<Material>();
            MSpike->BaseColour.TextureV3 = TSpike;

            //apply the material
            Spike6->SetMaterialBySlot(0, MSpike);

            //adding collision to spike
            Spike6->AddCollisionToModel(Vector3(1.0f, 1.0f, 1.0f));
        }
        if (Spike7 != nullptr) {
            //transform spike 7 model
            Spike7->Transform.Scale = Vector3(0.00009f);
            Spike7->Transform.Rotation.x = 90.0f;
            Spike7->Transform.Location = Vector3(120.0f, -2.5f, 10.0f);

            //create texture for spike
            TexturePtr TSpike = Graphics->CreateTexture("Game/Models/Spike/Spike.png");

            //create material
            MaterialPtr MSpike = make_shared<Material>();
            MSpike->BaseColour.TextureV3 = TSpike;

            //apply the material
            Spike7->SetMaterialBySlot(0, MSpike);

            //adding collision to spike
            Spike7->AddCollisionToModel(Vector3(1.0f, 1.0f, 1.0f));
        }
        if (Spike8 != nullptr) {
            //transform spike 8 model
            Spike8->Transform.Scale = Vector3(0.00009f);
            Spike8->Transform.Rotation.x = 90.0f;
            Spike8->Transform.Location = Vector3(140.0f, -2.5f, -7.0f);

            //create texture for spike
            TexturePtr TSpike = Graphics->CreateTexture("Game/Models/Spike/Spike.png");

            //create material
            MaterialPtr MSpike = make_shared<Material>();
            MSpike->BaseColour.TextureV3 = TSpike;

            //apply the material
            Spike8->SetMaterialBySlot(0, MSpike);

            //adding collision to spike
            Spike8->AddCollisionToModel(Vector3(1.0f, 1.0f, 1.0f));
        }
        if (Spike9 != nullptr) {
            //transform spike 9 model
            Spike9->Transform.Scale = Vector3(0.00009f);
            Spike9->Transform.Rotation.x = 90.0f;
            Spike9->Transform.Location = Vector3(165.0f, -2.5f, 1.0f);

            //create texture for spike
            TexturePtr TSpike = Graphics->CreateTexture("Game/Models/Spike/Spike.png");

            //create material
            MaterialPtr MSpike = make_shared<Material>();
            MSpike->BaseColour.TextureV3 = TSpike;

            //apply the material
            Spike9->SetMaterialBySlot(0, MSpike);

            //adding collision to spike
            Spike9->AddCollisionToModel(Vector3(1.0f, 1.0f, 1.0f));
        }
        if (Spike10 != nullptr) {
            //transform spike 10 model
            Spike10->Transform.Scale = Vector3(0.00009f);
            Spike10->Transform.Rotation.x = 90.0f;
            Spike10->Transform.Location = Vector3(170.0f, -2.5f, 2.0f);

            //create texture for spike
            TexturePtr TSpike = Graphics->CreateTexture("Game/Models/Spike/Spike.png");

            //create material
            MaterialPtr MSpike = make_shared<Material>();
            MSpike->BaseColour.TextureV3 = TSpike;

            //apply the material
            Spike10->SetMaterialBySlot(0, MSpike);

            //adding collision to spike
            Spike10->AddCollisionToModel(Vector3(1.0f, 1.0f, 1.0f));
        }
        if (Spike11 != nullptr) {
            //transform spike 11 model
            Spike11->Transform.Scale = Vector3(0.00009f);
            Spike11->Transform.Rotation.x = 90.0f;
            Spike11->Transform.Location = Vector3(180.0f, -2.5f, -7.0f);

            //create texture for spike
            TexturePtr TSpike = Graphics->CreateTexture("Game/Models/Spike/Spike.png");

            //create material
            MaterialPtr MSpike = make_shared<Material>();
            MSpike->BaseColour.TextureV3 = TSpike;

            //apply the material
            Spike11->SetMaterialBySlot(0, MSpike);

            //adding collision to spike
            Spike11->AddCollisionToModel(Vector3(1.0f, 1.0f, 1.0f));
        }
        if (Spike12 != nullptr) {
            //transform spike 12 model
            Spike12->Transform.Scale = Vector3(0.00009f);
            Spike12->Transform.Rotation.x = 90.0f;
            Spike12->Transform.Location = Vector3(180.0f, -2.5f, 3.0f);

            //create texture for spike
            TexturePtr TSpike = Graphics->CreateTexture("Game/Models/Spike/Spike.png");

            //create material
            MaterialPtr MSpike = make_shared<Material>();
            MSpike->BaseColour.TextureV3 = TSpike;

            //apply the material
            Spike12->SetMaterialBySlot(0, MSpike);

            //adding collision to spike
            Spike12->AddCollisionToModel(Vector3(1.0f, 1.0f, 1.0f));
        }
        if (Spike13 != nullptr) {
            //transform spike 13 model
            Spike13->Transform.Scale = Vector3(0.00009f);
            Spike13->Transform.Rotation.x = 90.0f;
            Spike13->Transform.Location = Vector3(225.0f, -2.5f, 0.0f);

            //create texture for spike
            TexturePtr TSpike = Graphics->CreateTexture("Game/Models/Spike/Spike.png");

            //create material
            MaterialPtr MSpike = make_shared<Material>();
            MSpike->BaseColour.TextureV3 = TSpike;

            //apply the material
            Spike13->SetMaterialBySlot(0, MSpike);

            //adding collision to spike
            Spike13->AddCollisionToModel(Vector3(1.0f, 1.0f, 1.0f));
        }
        if (Spike14 != nullptr) {
            //transform spike 14 model
            Spike14->Transform.Scale = Vector3(0.00009f);
            Spike14->Transform.Rotation.x = 90.0f;
            Spike14->Transform.Location = Vector3(255.0f, -2.5f, -4.0f);

            //create texture for spike
            TexturePtr TSpike = Graphics->CreateTexture("Game/Models/Spike/Spike.png");

            //create material
            MaterialPtr MSpike = make_shared<Material>();
            MSpike->BaseColour.TextureV3 = TSpike;

            //apply the material
            Spike14->SetMaterialBySlot(0, MSpike);

            //adding collision to spike
            Spike14->AddCollisionToModel(Vector3(1.0f, 1.0f, 1.0f));
        }

        if (Car != nullptr) {
            //transform coin model
            Car->Transform.Scale = Vector3(0.005f);
            Car->Transform.Rotation.x = -90.0f;
            Car->Transform.Rotation.z = -270.0f;
            Car->Transform.Location = Vector3(1.5f, -1.0f, 0.0f);

            //create texture for coin
            TexturePtr TCar = Graphics->CreateTexture("Game/Models/fallout-car/textures/default_Base_Color.png");
            TexturePtr SCar = Graphics->CreateTexture("Game/Models/fallout-car/textures/car_low_default_AmbientOcclusion.png");

            //create material
            MaterialPtr MCar = make_shared<Material>();
            MCar->BaseColour.TextureV3 = TCar;
            MCar->SpecularColour.TextureV3 = SCar;

            //apply the material
            Car->SetMaterialBySlot(0, MCar);
            Car->GetMaterialBySlot(0)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            //adding boxcollision for car
            Car->AddCollisionToModel(Vector3(3.5f, 0.9f, 1.8f), Vector3(-1.4f, 0.20f, 0.0f));
        }

        if (LWall1 != nullptr) {
            //transform the wall to the left
            LWall1->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            LWall1->Transform.Rotation.y = 90.0f;
            LWall1->Transform.Location = Vector3(14.0f, -3.0f, -15.0f);

            //transform wall to the right
            RWall1->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            RWall1->Transform.Rotation.y = 270.0f;
            RWall1->Transform.Location = Vector3(14.0f, -3.0f, 21.0f);

            //create the texture
            TexturePtr TWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Base_Color.jpeg");
            TexturePtr SWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Mixed_AO.jpeg.jpeg");

            //create a material
            MaterialPtr MWall = make_shared<Material>();
            MWall->BaseColour.TextureV3 = TWall;
            MWall->SpecularColour.TextureV3 = SWall;

            //apply the material
            LWall1->SetMaterialBySlot(1, MWall);
            LWall1->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            RWall1->SetMaterialBySlot(1, MWall);
            RWall1->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            //adding boxcollision
            LWall1->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));

            RWall1->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));
        }

        if (LWall2 != nullptr) {
            //transform the wall to the left
            LWall2->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            LWall2->Transform.Rotation.y = 90.0f;
            LWall2->Transform.Location = Vector3(14.0f * 2, -3.0f, -15.0f);

            //transform wall to the right
            RWall2->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            RWall2->Transform.Rotation.y = 270.0f;
            RWall2->Transform.Location = Vector3(14.0f * 2, -3.0f, 21.0f);

            //create the texture
            TexturePtr TWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Base_Color.jpeg");
            TexturePtr SWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Mixed_AO.jpeg.jpeg");

            //create a material
            MaterialPtr MWall = make_shared<Material>();
            MWall->BaseColour.TextureV3 = TWall;
            MWall->SpecularColour.TextureV3 = SWall;

            //apply the material
            LWall2->SetMaterialBySlot(1, MWall);
            LWall2->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            RWall2->SetMaterialBySlot(1, MWall);
            RWall2->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            //adding boxcollision
            LWall2->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));

            RWall2->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));
        }
        if (LWall3 != nullptr) {
            //transform the wall to the left
            LWall3->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            LWall3->Transform.Rotation.y = 90.0f;
            LWall3->Transform.Location = Vector3(14.0f * 3, -3.0f, -15.0f);

            //transform wall to the right
            RWall3->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            RWall3->Transform.Rotation.y = 270.0f;
            RWall3->Transform.Location = Vector3(14.0f * 3, -3.0f, 21.0f);

            //create the texture
            TexturePtr TWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Base_Color.jpeg");
            TexturePtr SWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Mixed_AO.jpeg.jpeg");

            //create a material
            MaterialPtr MWall = make_shared<Material>();
            MWall->BaseColour.TextureV3 = TWall;
            MWall->SpecularColour.TextureV3 = SWall;

            //apply the material
            LWall3->SetMaterialBySlot(1, MWall);
            LWall3->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            RWall3->SetMaterialBySlot(1, MWall);
            RWall3->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            //adding boxcollision
            LWall3->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));

            RWall3->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));
        }
        if (LWall4 != nullptr) {
            //transform the wall to the left
            LWall4->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            LWall4->Transform.Rotation.y = 90.0f;
            LWall4->Transform.Location = Vector3(14.0f * 4, -3.0f, -15.0f);

            //transform wall to the right
            RWall4->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            RWall4->Transform.Rotation.y = 270.0f;
            RWall4->Transform.Location = Vector3(14.0f * 4, -3.0f, 21.0f);

            //create the texture
            TexturePtr TWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Base_Color.jpeg");
            TexturePtr SWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Mixed_AO.jpeg.jpeg");

            //create a material
            MaterialPtr MWall = make_shared<Material>();
            MWall->BaseColour.TextureV3 = TWall;
            MWall->SpecularColour.TextureV3 = SWall;

            //apply the material
            LWall4->SetMaterialBySlot(1, MWall);
            LWall4->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            RWall4->SetMaterialBySlot(1, MWall);
            RWall4->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            //adding boxcollision
            LWall4->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));

            RWall4->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));
        }
        if (LWall5 != nullptr) {
            //transform the wall to the left
            LWall5->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            LWall5->Transform.Rotation.y = 90.0f;
            LWall5->Transform.Location = Vector3(14.0f * 5, -3.0f, -15.0f);

            //transform wall to the right
            RWall5->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            RWall5->Transform.Rotation.y = 270.0f;
            RWall5->Transform.Location = Vector3(14.0f * 5, -3.0f, 21.0f);

            //create the texture
            TexturePtr TWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Base_Color.jpeg");
            TexturePtr SWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Mixed_AO.jpeg.jpeg");

            //create a material
            MaterialPtr MWall = make_shared<Material>();
            MWall->BaseColour.TextureV3 = TWall;
            MWall->SpecularColour.TextureV3 = SWall;

            //apply the material
            LWall5->SetMaterialBySlot(1, MWall);
            LWall5->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            RWall5->SetMaterialBySlot(1, MWall);
            RWall5->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            //adding boxcollision
            LWall5->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));

            RWall5->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));
        }
        if (LWall6 != nullptr) {
            //transform the wall to the left
            LWall6->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            LWall6->Transform.Rotation.y = 90.0f;
            LWall6->Transform.Location = Vector3(14.0f * 6, -3.0f, -15.0f);

            //transform wall to the right
            RWall6->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            RWall6->Transform.Rotation.y = 270.0f;
            RWall6->Transform.Location = Vector3(14.0f * 6, -3.0f, 21.0f);

            //create the texture
            TexturePtr TWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Base_Color.jpeg");
            TexturePtr SWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Mixed_AO.jpeg.jpeg");

            //create a material
            MaterialPtr MWall = make_shared<Material>();
            MWall->BaseColour.TextureV3 = TWall;
            MWall->SpecularColour.TextureV3 = SWall;

            //apply the material
            LWall6->SetMaterialBySlot(1, MWall);
            LWall6->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            RWall6->SetMaterialBySlot(1, MWall);
            RWall6->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            //adding boxcollision
            LWall6->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));

            RWall6->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));
        }
        if (LWall7 != nullptr) {
            //transform the wall to the left
            LWall7->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            LWall7->Transform.Rotation.y = 90.0f;
            LWall7->Transform.Location = Vector3(14.0f * 7, -3.0f, -15.0f);

            //transform wall to the right
            RWall7->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            RWall7->Transform.Rotation.y = 270.0f;
            RWall7->Transform.Location = Vector3(14.0f * 7, -3.0f, 21.0f);

            //create the texture
            TexturePtr TWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Base_Color.jpeg");
            TexturePtr SWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Mixed_AO.jpeg.jpeg");

            //create a material
            MaterialPtr MWall = make_shared<Material>();
            MWall->BaseColour.TextureV3 = TWall;
            MWall->SpecularColour.TextureV3 = SWall;

            //apply the material
            LWall7->SetMaterialBySlot(1, MWall);
            LWall7->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            RWall7->SetMaterialBySlot(1, MWall);
            RWall7->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            //adding boxcollision
            LWall7->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));

            RWall7->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));
        }
        if (LWall8 != nullptr) {
            //transform the wall to the left
            LWall8->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            LWall8->Transform.Rotation.y = 90.0f;
            LWall8->Transform.Location = Vector3(14.0f * 8, -3.0f, -15.0f);

            //transform wall to the right
            RWall8->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            RWall8->Transform.Rotation.y = 270.0f;
            RWall8->Transform.Location = Vector3(14.0f * 8, -3.0f, 21.0f);

            //create the texture
            TexturePtr TWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Base_Color.jpeg");
            TexturePtr SWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Mixed_AO.jpeg.jpeg");

            //create a material
            MaterialPtr MWall = make_shared<Material>();
            MWall->BaseColour.TextureV3 = TWall;
            MWall->SpecularColour.TextureV3 = SWall;

            //apply the material
            LWall8->SetMaterialBySlot(1, MWall);
            LWall8->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            RWall8->SetMaterialBySlot(1, MWall);
            RWall8->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            //adding boxcollision
            LWall8->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));

            RWall8->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));
        }
        if (LWall9 != nullptr) {
            //transform the wall to the left
            LWall9->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            LWall9->Transform.Rotation.y = 90.0f;
            LWall9->Transform.Location = Vector3(14.0f * 9, -3.0f, -15.0f);

            //transform wall to the right
            RWall9->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            RWall9->Transform.Rotation.y = 270.0f;
            RWall9->Transform.Location = Vector3(14.0f * 9, -3.0f, 21.0f);

            //create the texture
            TexturePtr TWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Base_Color.jpeg");
            TexturePtr SWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Mixed_AO.jpeg.jpeg");

            //create a material
            MaterialPtr MWall = make_shared<Material>();
            MWall->BaseColour.TextureV3 = TWall;
            MWall->SpecularColour.TextureV3 = SWall;

            //apply the material
            LWall9->SetMaterialBySlot(1, MWall);
            LWall9->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            RWall9->SetMaterialBySlot(1, MWall);
            RWall9->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            //adding boxcollision
            LWall9->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));

            RWall9->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));
        }
        if (LWall10 != nullptr) {
            //transform the wall to the left
            LWall10->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            LWall10->Transform.Rotation.y = 90.0f;
            LWall10->Transform.Location = Vector3(14.0f * 10, -3.0f, -15.0f);

            //transform wall to the right
            RWall10->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            RWall10->Transform.Rotation.y = 270.0f;
            RWall10->Transform.Location = Vector3(14.0f * 10, -3.0f, 21.0f);

            //create the texture
            TexturePtr TWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Base_Color.jpeg");
            TexturePtr SWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Mixed_AO.jpeg.jpeg");

            //create a material
            MaterialPtr MWall = make_shared<Material>();
            MWall->BaseColour.TextureV3 = TWall;
            MWall->SpecularColour.TextureV3 = SWall;

            //apply the material
            LWall10->SetMaterialBySlot(1, MWall);
            LWall10->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            RWall10->SetMaterialBySlot(1, MWall);
            RWall10->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            //adding boxcollision
            LWall10->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));

            RWall10->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));
        }
        if (LWall11 != nullptr) {
            //transform the wall to the left
            LWall11->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            LWall11->Transform.Rotation.y = 90.0f;
            LWall11->Transform.Location = Vector3(14.0f * 11, -3.0f, -15.0f);

            //transform wall to the right
            RWall11->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            RWall11->Transform.Rotation.y = 270.0f;
            RWall11->Transform.Location = Vector3(14.0f * 11, -3.0f, 21.0f);

            //create the texture
            TexturePtr TWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Base_Color.jpeg");
            TexturePtr SWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Mixed_AO.jpeg.jpeg");

            //create a material
            MaterialPtr MWall = make_shared<Material>();
            MWall->BaseColour.TextureV3 = TWall;
            MWall->SpecularColour.TextureV3 = SWall;

            //apply the material
            LWall11->SetMaterialBySlot(1, MWall);
            LWall11->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            RWall11->SetMaterialBySlot(1, MWall);
            RWall11->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            //adding boxcollision
            LWall11->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));

            RWall11->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));
        }
        if (LWall12 != nullptr) {
            //transform the wall to the left
            LWall12->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            LWall12->Transform.Rotation.y = 90.0f;
            LWall12->Transform.Location = Vector3(14.0f * 12, -3.0f, -15.0f);

            //transform wall to the right
            RWall12->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            RWall12->Transform.Rotation.y = 270.0f;
            RWall12->Transform.Location = Vector3(14.0f * 12, -3.0f, 21.0f);

            //create the texture
            TexturePtr TWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Base_Color.jpeg");
            TexturePtr SWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Mixed_AO.jpeg.jpeg");

            //create a material
            MaterialPtr MWall = make_shared<Material>();
            MWall->BaseColour.TextureV3 = TWall;
            MWall->SpecularColour.TextureV3 = SWall;

            //apply the material
            LWall12->SetMaterialBySlot(1, MWall);
            LWall12->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            RWall12->SetMaterialBySlot(1, MWall);
            RWall12->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            //adding boxcollision
            LWall12->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));

            RWall12->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));
        }
        if (LWall13 != nullptr) {
            //transform the wall to the left
            LWall13->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            LWall13->Transform.Rotation.y = 90.0f;
            LWall13->Transform.Location = Vector3(14.0f * 13, -3.0f, -15.0f);

            //transform wall to the right
            RWall13->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            RWall13->Transform.Rotation.y = 270.0f;
            RWall13->Transform.Location = Vector3(14.0f * 13, -3.0f, 21.0f);

            //create the texture
            TexturePtr TWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Base_Color.jpeg");
            TexturePtr SWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Mixed_AO.jpeg.jpeg");

            //create a material
            MaterialPtr MWall = make_shared<Material>();
            MWall->BaseColour.TextureV3 = TWall;
            MWall->SpecularColour.TextureV3 = SWall;

            //apply the material
            LWall13->SetMaterialBySlot(1, MWall);
            LWall13->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            RWall13->SetMaterialBySlot(1, MWall);
            RWall13->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            //adding boxcollision
            LWall13->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));

            RWall13->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));
        }
        if (LWall14 != nullptr) {
            //transform the wall to the left
            LWall14->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            LWall14->Transform.Rotation.y = 90.0f;
            LWall14->Transform.Location = Vector3(14.0f * 14, -3.0f, -15.0f);

            //transform wall to the right
            RWall14->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            RWall14->Transform.Rotation.y = 270.0f;
            RWall14->Transform.Location = Vector3(14.0f * 14, -3.0f, 21.0f);

            //create the texture
            TexturePtr TWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Base_Color.jpeg");
            TexturePtr SWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Mixed_AO.jpeg.jpeg");

            //create a material
            MaterialPtr MWall = make_shared<Material>();
            MWall->BaseColour.TextureV3 = TWall;
            MWall->SpecularColour.TextureV3 = SWall;

            //apply the material
            LWall14->SetMaterialBySlot(1, MWall);
            LWall14->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            RWall14->SetMaterialBySlot(1, MWall);
            RWall14->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            //adding boxcollision
            LWall14->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));

            RWall14->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));
        }
        if (LWall15 != nullptr) {
            //transform the wall to the left
            LWall15->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            LWall15->Transform.Rotation.y = 90.0f;
            LWall15->Transform.Location = Vector3(14.0f * 15, -3.0f, -15.0f);

            //transform wall to the right
            RWall15->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            RWall15->Transform.Rotation.y = 270.0f;
            RWall15->Transform.Location = Vector3(14.0f * 15, -3.0f, 21.0f);

            //create the texture
            TexturePtr TWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Base_Color.jpeg");
            TexturePtr SWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Mixed_AO.jpeg.jpeg");

            //create a material
            MaterialPtr MWall = make_shared<Material>();
            MWall->BaseColour.TextureV3 = TWall;
            MWall->SpecularColour.TextureV3 = SWall;

            //apply the material
            LWall15->SetMaterialBySlot(1, MWall);
            LWall15->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            RWall15->SetMaterialBySlot(1, MWall);
            RWall15->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            //adding boxcollision
            LWall15->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));

            RWall15->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));
        }
        if (LWall16 != nullptr) {
            //transform the wall to the left
            LWall16->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            LWall16->Transform.Rotation.y = 90.0f;
            LWall16->Transform.Location = Vector3(14.0f * 16, -3.0f, -15.0f);

            //transform wall to the right
            RWall16->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            RWall16->Transform.Rotation.y = 270.0f;
            RWall16->Transform.Location = Vector3(14.0f * 16, -3.0f, 21.0f);

            //create the texture
            TexturePtr TWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Base_Color.jpeg");
            TexturePtr SWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Mixed_AO.jpeg.jpeg");

            //create a material
            MaterialPtr MWall = make_shared<Material>();
            MWall->BaseColour.TextureV3 = TWall;
            MWall->SpecularColour.TextureV3 = SWall;

            //apply the material
            LWall16->SetMaterialBySlot(1, MWall);
            LWall16->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            RWall16->SetMaterialBySlot(1, MWall);
            RWall16->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            //adding boxcollision
            LWall16->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));

            RWall16->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));
        }
        if (LWall17 != nullptr) {
            //transform the wall to the left
            LWall17->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            LWall17->Transform.Rotation.y = 90.0f;
            LWall17->Transform.Location = Vector3(14.0f * 17, -3.0f, -15.0f);

            //transform wall to the right
            RWall17->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            RWall17->Transform.Rotation.y = 270.0f;
            RWall17->Transform.Location = Vector3(14.0f * 17, -3.0f, 21.0f);

            //create the texture
            TexturePtr TWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Base_Color.jpeg");
            TexturePtr SWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Mixed_AO.jpeg.jpeg");

            //create a material
            MaterialPtr MWall = make_shared<Material>();
            MWall->BaseColour.TextureV3 = TWall;
            MWall->SpecularColour.TextureV3 = SWall;

            //apply the material
            LWall17->SetMaterialBySlot(1, MWall);
            LWall17->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            RWall17->SetMaterialBySlot(1, MWall);
            RWall17->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            //adding boxcollision
            LWall17->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));

            RWall17->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));
        }
        if (LWall18 != nullptr) {
            //transform the wall to the left
            LWall18->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            LWall18->Transform.Rotation.y = 90.0f;
            LWall18->Transform.Location = Vector3(14.0f * 18, -3.0f, -15.0f);

            //transform wall to the right
            RWall18->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            RWall18->Transform.Rotation.y = 270.0f;
            RWall18->Transform.Location = Vector3(14.0f * 18, -3.0f, 21.0f);

            //create the texture
            TexturePtr TWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Base_Color.jpeg");
            TexturePtr SWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Mixed_AO.jpeg.jpeg");

            //create a material
            MaterialPtr MWall = make_shared<Material>();
            MWall->BaseColour.TextureV3 = TWall;
            MWall->SpecularColour.TextureV3 = SWall;

            //apply the material
            LWall18->SetMaterialBySlot(1, MWall);
            LWall18->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            RWall18->SetMaterialBySlot(1, MWall);
            RWall18->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            //adding boxcollision
            LWall18->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));

            RWall18->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));
        }
        if (LWall19 != nullptr) {
            //transform the wall to the left
            LWall19->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            LWall19->Transform.Rotation.y = 90.0f;
            LWall19->Transform.Location = Vector3(14.0f * 19, -3.0f, -15.0f);

            //transform wall to the right
            RWall19->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            RWall19->Transform.Rotation.y = 270.0f;
            RWall19->Transform.Location = Vector3(14.0f * 19, -3.0f, 21.0f);

            //create the texture
            TexturePtr TWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Base_Color.jpeg");
            TexturePtr SWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Mixed_AO.jpeg.jpeg");

            //create a material
            MaterialPtr MWall = make_shared<Material>();
            MWall->BaseColour.TextureV3 = TWall;
            MWall->SpecularColour.TextureV3 = SWall;

            //apply the material
            LWall19->SetMaterialBySlot(1, MWall);
            LWall19->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            RWall19->SetMaterialBySlot(1, MWall);
            RWall19->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            //adding boxcollision
            LWall19->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));

            RWall19->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));
        }
        if (LWall20 != nullptr) {
            //transform the wall to the left
            LWall20->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            LWall20->Transform.Rotation.y = 90.0f;
            LWall20->Transform.Location = Vector3(14.0f * 20, -3.0f, -15.0f);

            //transform wall to the right
            RWall20->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            RWall20->Transform.Rotation.y = 270.0f;
            RWall20->Transform.Location = Vector3(14.0f * 20, -3.0f, 21.0f);

            //create the texture
            TexturePtr TWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Base_Color.jpeg");
            TexturePtr SWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Mixed_AO.jpeg.jpeg");

            //create a material
            MaterialPtr MWall = make_shared<Material>();
            MWall->BaseColour.TextureV3 = TWall;
            MWall->SpecularColour.TextureV3 = SWall;

            //apply the material
            LWall20->SetMaterialBySlot(1, MWall);
            LWall20->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            RWall20->SetMaterialBySlot(1, MWall);
            RWall20->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            //adding boxcollision
            LWall20->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));

            RWall20->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));
        }
        if (LWall21 != nullptr) {
            //transform the wall to the left
            LWall21->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            LWall21->Transform.Rotation.y = 90.0f;
            LWall21->Transform.Location = Vector3(0.0f, -3.0f, -15.0f);

            //transform wall to the right
            RWall21->Transform.Scale = Vector3(1.0f, 0.6, 1.0f);
            RWall21->Transform.Rotation.y = 270.0f;
            RWall21->Transform.Location = Vector3(0.0f, -3.0f, 21.0f);

            //create the texture
            TexturePtr TWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Base_Color.jpeg");
            TexturePtr SWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Mixed_AO.jpeg.jpeg");

            //create a material
            MaterialPtr MWall = make_shared<Material>();
            MWall->BaseColour.TextureV3 = TWall;
            MWall->SpecularColour.TextureV3 = SWall;

            //apply the material
            LWall21->SetMaterialBySlot(1, MWall);
            LWall21->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            RWall21->SetMaterialBySlot(1, MWall);
            RWall21->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            //adding boxcollision
            LWall21->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));

            RWall21->AddCollisionToModel(Vector3(14.0f, 3.0f, 3.0f), Vector3(1.0f, 1.5f, -0.5));
        }
        if (StartWall != nullptr) {
            //transform the wall to the left
            StartWall->Transform.Scale = Vector3(1.0f, 0.35, 3.0f);
            StartWall->Transform.Rotation.y = 0.0f;
            StartWall->Transform.Location = Vector3(-2.0f, -3.0f, 0.0f);

            //transform wall to the right
            EndWall->Transform.Scale = Vector3(1.0f, 0.35, 3.0f);
            EndWall->Transform.Rotation.y = 0.0f;
            EndWall->Transform.Location = Vector3(270.0f, -3.0f, 0.0f);

            //create the texture
            TexturePtr TWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Base_Color.jpeg");
            TexturePtr SWall = Graphics->CreateTexture("Game/Models/road-barrier/textures/barier_Mixed_AO.jpeg.jpeg");

            //create a material
            MaterialPtr MWall = make_shared<Material>();
            MWall->BaseColour.TextureV3 = TWall;
            MWall->SpecularColour.TextureV3 = SWall;

            //apply the material
            StartWall->SetMaterialBySlot(1, MWall);
            StartWall->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            EndWall->SetMaterialBySlot(1, MWall);
            EndWall->GetMaterialBySlot(1)->SpecularColour.MultiplierV3 = Vector3(1.0f);

            //adding boxcollision
            StartWall->AddCollisionToModel(Vector3(10.0f, 3.0f, 3.0f), Vector3(-5.0f, 1.5f, -0.5));

            EndWall->AddCollisionToModel(Vector3(10.0f, 3.0f, 3.0f), Vector3(-5.0f, 1.5f, -0.5));
        }
    }
    
    //as long as the game is not over
    while (!bIsGameOver) {
        //make sure we process the user input
        ProcessInput();

        //apply logic based on the inputs and game logic
        Update();

        //render the screen based on the functions above
        Draw();
    }

    CloseGame();
}

void Game::ProcessInput()
{
    //run the input detection for our game input
    GameInput->ProcessInput();

    Vector3 CameraInput = Vector3(0.0f);

    CDirections CamDirection = Graphics->EngineDefaultCam->GetDirections();

    Graphics->EngineDefaultCam->GetCameraData().FarClip;

    //move camera foward
    if (GameInput->IsKeyDown(SDL_SCANCODE_W)) {
        CameraInput += CamDirection.Forward;
        Car->Transform.Rotation.z = -270.0f;
    }
    //move camera backward
    if (GameInput->IsKeyDown(SDL_SCANCODE_S)) {
        CameraInput += -CamDirection.Forward;
        Car->Transform.Rotation.z = -270.0f;
    }
    //move camera left
    if (GameInput->IsKeyDown(SDL_SCANCODE_A)) {
        CameraInput += -CamDirection.Right;
        Car->Transform.Rotation.z += 0.05f;
    }
    //move camera right
    if (GameInput->IsKeyDown(SDL_SCANCODE_D)) {
        CameraInput += CamDirection.Right;
        Car->Transform.Rotation.z -= 0.05f;
    }
    //move camera up
    if (GameInput->IsKeyDown(SDL_SCANCODE_Q)) {
        CameraInput += -CamDirection.Up;
    }//move camera down
    if (GameInput->IsKeyDown(SDL_SCANCODE_E)) {
        CameraInput += CamDirection.Up;
    }

    //move the camera based on input
    Graphics->EngineDefaultCam->AddMovementInput(CameraInput);
    Car->Transform.Location.x = Graphics->EngineDefaultCam->GetTransforms().Location.x + 5.0f;
    Car->Transform.Location.y = -1.5f;
    Car->Transform.Location.z = Graphics->EngineDefaultCam->GetTransforms().Location.z;

    if (GameInput->IsMouseButtonDown(MouseButtons::RIGHT)) {
        Graphics->EngineDefaultCam->RotatePitch(-GameInput->MouseYDelta);
        Graphics->EngineDefaultCam->RotateYaw(GameInput->MouseXDelta);
        GameInput->ShowCursor(false);
    }
    else {
        GameInput->ShowCursor(true);
    }
}

void Game::Update()
{
    //Set delta time first always
    static double LastFrameTime = 0.0;
    //Set the current time since the game has passed
    double CurrentFrameTime = static_cast<double>(SDL_GetTicks64());
    //find the time difference between last and current frame
    double NewDeltaTime = CurrentFrameTime - LastFrameTime;
    //set delta time as seconds
    DeltaTime = NewDeltaTime / 1000.0;
    //update the last frame tiem for the next update
    LastFrameTime = CurrentFrameTime;

    Coin1->Transform.Rotation.z += 150.0f * GetFDeltaTime();
    Coin2->Transform.Rotation.z += 150.0f * GetFDeltaTime();
    Coin3->Transform.Rotation.z += 150.0f * GetFDeltaTime();
    Coin4->Transform.Rotation.z += 150.0f * GetFDeltaTime();
    Coin5->Transform.Rotation.z += 150.0f * GetFDeltaTime();
    Coin6->Transform.Rotation.z += 150.0f * GetFDeltaTime();
    Coin7->Transform.Rotation.z += 150.0f * GetFDeltaTime();
    Coin8->Transform.Rotation.z += 150.0f * GetFDeltaTime();
    Coin9->Transform.Rotation.z += 150.0f * GetFDeltaTime();
    Coin10->Transform.Rotation.z += 150.0f * GetFDeltaTime();
    Coin11->Transform.Rotation.z += 150.0f * GetFDeltaTime();
    Coin12->Transform.Rotation.z += 150.0f * GetFDeltaTime();
    Coin13->Transform.Rotation.z += 150.0f * GetFDeltaTime();
    Coin14->Transform.Rotation.z += 150.0f * GetFDeltaTime();
    Coin15->Transform.Rotation.z += 150.0f * GetFDeltaTime();
    Coin16->Transform.Rotation.z += 150.0f * GetFDeltaTime();
    Coin17->Transform.Rotation.z += 150.0f * GetFDeltaTime();
    Coin18->Transform.Rotation.z += 150.0f * GetFDeltaTime();

    Graphics->EngineDefaultCam->Update();

    //camera collision stuff
    CollisionPtr CarCol = Car->GetCollision();

	if (Coin1 != nullptr && CarCol->IsOverlapping(*Coin1->GetCollision())) {
		//remove coins if colliding with coins
		RemoveModelFromGame(Coin1);
	}
    if (Coin2 != nullptr && CarCol->IsOverlapping(*Coin2->GetCollision())) {
        //remove coins if colliding with coins
        RemoveModelFromGame(Coin2);
    }
    if (Coin3 != nullptr && CarCol->IsOverlapping(*Coin3->GetCollision())) {
        //remove coins if colliding with coins
        RemoveModelFromGame(Coin3);
    }
    if (Coin4 != nullptr && CarCol->IsOverlapping(*Coin4->GetCollision())) {
        //remove coins if colliding with coins
        RemoveModelFromGame(Coin4);
    }
    if (Coin5 != nullptr && CarCol->IsOverlapping(*Coin5->GetCollision())) {
        //remove coins if colliding with coins
        RemoveModelFromGame(Coin5);
    }
    if (Coin6 != nullptr && CarCol->IsOverlapping(*Coin6->GetCollision())) {
        //remove coins if colliding with coins
        RemoveModelFromGame(Coin6);
    }
    if (Coin7 != nullptr && CarCol->IsOverlapping(*Coin7->GetCollision())) {
        //remove coins if colliding with coins
        RemoveModelFromGame(Coin7);
    }
    if (Coin8 != nullptr && CarCol->IsOverlapping(*Coin8->GetCollision())) {
        //remove coins if colliding with coins
        RemoveModelFromGame(Coin8);
    }
    if (Coin9 != nullptr && CarCol->IsOverlapping(*Coin9->GetCollision())) {
        //remove coins if colliding with coins
        RemoveModelFromGame(Coin9);
    }
    if (Coin10 != nullptr && CarCol->IsOverlapping(*Coin10->GetCollision())) {
        //remove coins if colliding with coins
        RemoveModelFromGame(Coin10);
    }
    if (Coin11 != nullptr && CarCol->IsOverlapping(*Coin11->GetCollision())) {
        //remove coins if colliding with coins
        RemoveModelFromGame(Coin1);
    }
    if (Coin12 != nullptr && CarCol->IsOverlapping(*Coin12->GetCollision())) {
        //remove coins if colliding with coins
        RemoveModelFromGame(Coin12);
    }
    if (Coin13 != nullptr && CarCol->IsOverlapping(*Coin13->GetCollision())) {
        //remove coins if colliding with coins
        RemoveModelFromGame(Coin13);
    }
    if (Coin14 != nullptr && CarCol->IsOverlapping(*Coin14->GetCollision())) {
        //remove coins if colliding with coins
        RemoveModelFromGame(Coin14);
    }
    if (Coin15 != nullptr && CarCol->IsOverlapping(*Coin15->GetCollision())) {
        //remove coins if colliding with coins
        RemoveModelFromGame(Coin15);
    }
    if (Coin16 != nullptr && CarCol->IsOverlapping(*Coin16->GetCollision())) {
        //remove coins if colliding with coins
        RemoveModelFromGame(Coin16);
    }
    if (Coin17 != nullptr && CarCol->IsOverlapping(*Coin17->GetCollision())) {
        //remove coins if colliding with coins
        RemoveModelFromGame(Coin17);
    }
    if (Coin18 != nullptr && CarCol->IsOverlapping(*Coin18->GetCollision())) {
        //remove coins if colliding with coins
        RemoveModelFromGame(Coin18);
    }

	if (LWall1 != nullptr && CarCol->IsOverlapping(*LWall1->GetCollision()) || (RWall1 != nullptr && CarCol->IsOverlapping(*RWall1->GetCollision()))) {
		//close game if colliding with wall
		RemoveModelFromGame(Car);
		SDL_Delay(1000);
		CloseGame();
	}
    if (LWall2 != nullptr && CarCol->IsOverlapping(*LWall2->GetCollision()) || (RWall2 != nullptr && CarCol->IsOverlapping(*RWall2->GetCollision()))) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (LWall3 != nullptr && CarCol->IsOverlapping(*LWall3->GetCollision()) || (RWall3 != nullptr && CarCol->IsOverlapping(*RWall3->GetCollision()))) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (LWall4 != nullptr && CarCol->IsOverlapping(*LWall4->GetCollision()) || (RWall4 != nullptr && CarCol->IsOverlapping(*RWall4->GetCollision()))) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (LWall5 != nullptr && CarCol->IsOverlapping(*LWall5->GetCollision()) || (RWall5 != nullptr && CarCol->IsOverlapping(*RWall5->GetCollision()))) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (LWall6 != nullptr && CarCol->IsOverlapping(*LWall6->GetCollision()) || (RWall6 != nullptr && CarCol->IsOverlapping(*RWall7->GetCollision()))) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (LWall7 != nullptr && CarCol->IsOverlapping(*LWall7->GetCollision()) || (RWall7 != nullptr && CarCol->IsOverlapping(*RWall7->GetCollision()))) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (LWall8 != nullptr && CarCol->IsOverlapping(*LWall8->GetCollision()) || (RWall8 != nullptr && CarCol->IsOverlapping(*RWall8->GetCollision()))) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (LWall9 != nullptr && CarCol->IsOverlapping(*LWall9->GetCollision()) || (RWall9 != nullptr && CarCol->IsOverlapping(*RWall9->GetCollision()))) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (LWall10 != nullptr && CarCol->IsOverlapping(*LWall10->GetCollision()) || (RWall10 != nullptr && CarCol->IsOverlapping(*RWall10->GetCollision()))) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (LWall11 != nullptr && CarCol->IsOverlapping(*LWall11->GetCollision()) || (RWall11 != nullptr && CarCol->IsOverlapping(*RWall11->GetCollision()))) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (LWall12 != nullptr && CarCol->IsOverlapping(*LWall12->GetCollision()) || (RWall12 != nullptr && CarCol->IsOverlapping(*RWall12->GetCollision()))) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (LWall13 != nullptr && CarCol->IsOverlapping(*LWall13->GetCollision()) || (RWall13 != nullptr && CarCol->IsOverlapping(*RWall13->GetCollision()))) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (LWall14 != nullptr && CarCol->IsOverlapping(*LWall14->GetCollision()) || (RWall14 != nullptr && CarCol->IsOverlapping(*RWall14->GetCollision()))) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (LWall15 != nullptr && CarCol->IsOverlapping(*LWall15->GetCollision()) || (RWall15 != nullptr && CarCol->IsOverlapping(*RWall15->GetCollision()))) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (LWall16 != nullptr && CarCol->IsOverlapping(*LWall16->GetCollision()) || (RWall16 != nullptr && CarCol->IsOverlapping(*RWall16->GetCollision()))) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (LWall17 != nullptr && CarCol->IsOverlapping(*LWall17->GetCollision()) || (RWall17 != nullptr && CarCol->IsOverlapping(*RWall17->GetCollision()))) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (LWall18 != nullptr && CarCol->IsOverlapping(*LWall18->GetCollision()) || (RWall18 != nullptr && CarCol->IsOverlapping(*RWall18->GetCollision()))) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (LWall19 != nullptr && CarCol->IsOverlapping(*LWall19->GetCollision()) || (RWall19 != nullptr && CarCol->IsOverlapping(*RWall19->GetCollision()))) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (LWall20 != nullptr && CarCol->IsOverlapping(*LWall20->GetCollision()) || (RWall20 != nullptr && CarCol->IsOverlapping(*RWall20->GetCollision()))) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (LWall21 != nullptr && CarCol->IsOverlapping(*LWall21->GetCollision()) || (RWall21 != nullptr && CarCol->IsOverlapping(*RWall21->GetCollision()))) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (StartWall != nullptr && CarCol->IsOverlapping(*StartWall->GetCollision())) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (EndWall != nullptr && CarCol->IsOverlapping(*EndWall->GetCollision())) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }

    if (Spike1 != nullptr && CarCol->IsOverlapping(*Spike1->GetCollision())) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (Spike2 != nullptr && CarCol->IsOverlapping(*Spike2->GetCollision())) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (Spike3 != nullptr && CarCol->IsOverlapping(*Spike3->GetCollision())) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (Spike4 != nullptr && CarCol->IsOverlapping(*Spike4->GetCollision())) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (Spike5 != nullptr && CarCol->IsOverlapping(*Spike5->GetCollision())) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (Spike6 != nullptr && CarCol->IsOverlapping(*Spike6->GetCollision())) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (Spike7 != nullptr && CarCol->IsOverlapping(*Spike7->GetCollision())) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (Spike8 != nullptr && CarCol->IsOverlapping(*Spike8->GetCollision())) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (Spike9 != nullptr && CarCol->IsOverlapping(*Spike9->GetCollision())) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (Spike10 != nullptr && CarCol->IsOverlapping(*Spike10->GetCollision())) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (Spike11 != nullptr && CarCol->IsOverlapping(*Spike11->GetCollision())) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (Spike12 != nullptr && CarCol->IsOverlapping(*Spike12->GetCollision())) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (Spike13 != nullptr && CarCol->IsOverlapping(*Spike13->GetCollision())) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
    if (Spike14 != nullptr && CarCol->IsOverlapping(*Spike14->GetCollision())) {
        //close game if colliding with wall
        RemoveModelFromGame(Car);
        SDL_Delay(1000);
        CloseGame();
    }
}

void Game::Draw()
{
    Graphics->ClearGraphics();

    //draw graphics to screen
    Graphics->Draw();

    //debug draw the camera collision
    CollisionPtr CarCol = Car->GetCollision();

    Graphics->PresentGraphics();
}

void Game::CloseGame()
{
    delete GameInput;
}
