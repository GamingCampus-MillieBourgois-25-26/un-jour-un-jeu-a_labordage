#include "Engine.h"
#include "SceneModule.h"
#include "Scenes/Demo/DemoScene.h"
#include "Scenes/Tetris/TetrisScene.h"
#include "BulletHelScene.h"

int main(const int _argc, const char** _argv)
{
    Engine* const engine = Engine::GetInstance();

    engine->Init(_argc, _argv);

    engine->GetModuleManager()->GetModule<SceneModule>()->SetScene<BulletHell::BulletHelScene>();

    engine->Run();

    return 0;
}
