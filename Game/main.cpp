#include "Engine.h"
#include "SceneModule.h"
#include "Scenes/Demo/DemoScene.h"
#include "Scenes/Tetris/TetrisScene.h"
#include "Scenes/BulletHell/BulletScene.h"
#include "Scenes/Runner/RunnerScene.h"
#include "Scenes/M_Tetris/M_TetrisScene.h"
#include "Scenes/Platformer/Platformer.h"
#include "Scenes/M_BulletHell/BulletHelScene.h"
#include "Scenes/M_TopDown/Topdownscene.h"
#include "iostream"

int main(const int _argc, const char** _argv)
{
    Engine* const engine = Engine::GetInstance();

    engine->Init(_argc, _argv);

    engine->GetModuleManager()->GetModule<SceneModule>()->RegisterSceneCreationFunction<Demo::DemoScene>();
    //engine->GetModuleManager()->GetModule<SceneModule>()->RegisterSceneCreationFunction<Platformer::Platformer>();
    //engine->GetModuleManager()->GetModule<SceneModule>()->RegisterSceneCreationFunction<M_BulletHell::BulletHelScene>();
    engine->GetModuleManager()->GetModule<SceneModule>()->RegisterSceneCreationFunction<M_TopDown::TopDownScene>();
    engine->GetModuleManager()->GetModule<SceneModule>()->RegisterSceneCreationFunction<Runner::RunnerScene>();
    engine->GetModuleManager()->GetModule<SceneModule>()->RegisterSceneCreationFunction<Tetris::M_TetrisScene>();

    
    
    engine->GetModuleManager()->GetModule<SceneModule>()->SetScene<Tetris::M_TetrisScene>();
    engine->Run();

    return 0;
}
