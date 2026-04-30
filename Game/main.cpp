#include "Engine.h"
#include "SceneModule.h"
#include "Scenes/Demo/DemoScene.h"
#include "Scenes/Tetris/TetrisScene.h"
#include "Scenes/BulletHell/BulletScene.h"
#include "Scenes/Runner/RunnerScene.h"
#include "Scenes/Platformer/Platformer.h"
#include "iostream"

int main(const int _argc, const char** _argv)
{
    Engine* const engine = Engine::GetInstance();

    engine->Init(_argc, _argv);

    engine->GetModuleManager()->GetModule<SceneModule>()->RegisterSceneCreationFunction<Demo::DemoScene>();
    engine->GetModuleManager()->GetModule<SceneModule>()->RegisterSceneCreationFunction<Platformer::Platformer>();

    engine->GetModuleManager()->GetModule<SceneModule>()->SetScene<Platformer::Platformer>();
    
    
    engine->Run();

    return 0;
}
