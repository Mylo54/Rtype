/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Settings
*/

#include "Settings.hpp"

rtp::Settings::Settings(scene_package_t pack): AScene(pack)
{
}

rtp::Settings::~Settings()
{
}

void rtp::Settings::setupScene()
{
    setupRegistry();
    addElements();
}

void rtp::Settings::setupRegistry()
{
    _reg.registerComponents(eng::SparseArray<eng::Velocity>());
    _reg.registerComponents(eng::SparseArray<eng::Position>());
    _reg.registerComponents(eng::SparseArray<eng::Drawable>());
    _reg.registerComponents(eng::SparseArray<eng::Sound>());
    _reg.registerComponents(eng::SparseArray<eng::RectCollider>());
    _reg.registerComponents(eng::SparseArray<eng::Writable>());
    _reg.registerComponents(eng::SparseArray<eng::Music>());
    _reg.registerComponents(eng::SparseArray<eng::ParticleEmitter>());
    _reg.registerComponents(eng::SparseArray<eng::RigidBody>());
    _reg.registerComponents(eng::SparseArray<rtp::Background>());
    _reg.registerComponents(eng::SparseArray<rtp::Button>());
}

void rtp::Settings::systemRun()
{
    // Update input events
    _input.updateEvents();

    if (_input.isActionJustPressed("ui_escape"))
        _sceneEvent = 1;
    // Animate buttons
    _buttonSystem.buttonStateSystem(_reg, _input);
    // Apply button actions
    _buttonSystem.buttonClick(_reg, _input);

    _physic.applyVelocities(_reg);

    // Play sounds & music
    _audio.playMusic(_reg);
    _audio.playSound(_reg);

    // clear, draw & display
    _graphic.clear();
    _graphic.animateSystem(_reg);
    _graphic.particleSystem(_reg);
    _graphic.drawSystem(_reg);
    _graphic.writeSystem(_reg);
    _graphic.display();
}

void rtp::Settings::addElements()
{
    addBackgrounds();
    _addTitle();
    _addFrameRateButton();
    _addFrameRateText();
    _addMusicButton();
    _addMusicText();
    _addMusic();
    _addSfxButton();
    _addSfxText();
    _addSfx();
}

void rtp::Settings::_addMusic()
{
    eng::Entity music = _reg.spawnEntity();

    _reg.addComponent<eng::Music>(music, eng::Music("assets/music.ogg", true));
}

void rtp::Settings::_addSfx()
{
    eng::Entity sfx = _reg.spawnEntity();

    _reg.addComponent<eng::Sound>(sfx, eng::Sound("assets/fire.wav", true));
}

void rtp::Settings::addBackgrounds()
{
    eng::Entity bg = _reg.spawnEntity();
    _reg.addComponent<eng::Velocity>(bg, eng::Velocity(-20, 0));
    _reg.addComponent<eng::Position>(bg, eng::Position(0, 0, 0));
    _reg.addComponent<eng::Drawable>(bg, eng::Drawable(_texture.getTextureFromFile("assets/background.png")));
    _reg.addComponent<rtp::Background>(bg, rtp::Background());
    eng::Entity bg2 = _reg.spawnEntity();
    _reg.addComponent<eng::Velocity>(bg2, eng::Velocity(-50, 0));
    _reg.addComponent<eng::Position>(bg2, eng::Position(0, 0, 0));
    _reg.addComponent<eng::Drawable>(bg2, eng::Drawable(_texture.getTextureFromFile("assets/middleground.png")));
    _reg.addComponent<rtp::Background>(bg2, rtp::Background());
    // eng::Entity bg3 = _reg.spawnEntity();
    // _reg.addComponent<eng::Position>(bg3, eng::Position(0, 0, 0));
    // _reg.addComponent<eng::Drawable>(bg3, eng::Drawable(_texture.getTextureFromFile("assets/foreground.png")));
    // _reg.addComponent<rtp::Background>(bg3, rtp::Background());
}

void rtp::Settings::_addTitle()
{
    eng::Entity text = _reg.spawnEntity();
    int scale = 5;

    _reg.addComponent<eng::Writable>(text, eng::Writable("Title", "Settings", "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(text, eng::Position(850, 200, 0));
}

void rtp::Settings::_addFrameRateButton()
{
    eng::Entity btn = _reg.spawnEntity();
    eng::Entity btntesxt = _reg.spawnEntity();
    int scale = 2;
    std::function<int()> frameRate = std::bind(&Settings::_frameRateBtnFunction, this);

    _reg.addComponent<eng::Position>(btn, eng::Position(950, 400, 0));
    _reg.addComponent<rtp::Button>(btn, rtp::Button(frameRate, 0, 0, 128 * 4, 32 * 1.5));
    _reg.addComponent<eng::Drawable>(btn, eng::Drawable(_texture.getTextureFromFile("assets/button.png"), 3, {0, 0, 28, 32}));

    unsigned int fpsValue = _graphic.getFrameRateLimit();
    std::stringstream ss;
    ss << fpsValue;
    _reg.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
    _reg.addComponent<eng::Writable>(btntesxt, eng::Writable("FPSButtonText", ss.str(), "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(btntesxt, eng::Position(985, 403, 0));
}

void rtp::Settings::_addFrameRateText()
{
    eng::Entity text = _reg.spawnEntity();
    int scale = 2;

    _reg.addComponent<eng::Writable>(text, eng::Writable("FPSText", "FPS   :", "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(text, eng::Position(800, 403, 0));
}

int rtp::Settings::_frameRateBtnFunction()
{
    unsigned int fpsValue = _graphic.getFrameRateLimit();
    std::stringstream ss;
    // ss << fpsValue;
    auto &texts = _reg.getComponents<eng::Writable>();

    for (int i = 0; i < texts.size(); i++) {
        if (texts[i].has_value() && texts[i].value()._name == "FPSButtonText") {
            if (fpsValue == 120) {
                texts[i].value()._txt.setString("30");
                _graphic.setFrameRateLimit(30);
            }
            else {
                ss << (fpsValue + 10);
                texts[i].value()._txt.setString(ss.str());
                _graphic.setFrameRateLimit(fpsValue + 10);
            }
        }
    }
    return (0);
}

void rtp::Settings::_addMusicButton()
{
    eng::Entity btn = _reg.spawnEntity();
    eng::Entity btntesxt = _reg.spawnEntity();
    int scale = 2;
    std::function<int()> music = std::bind(&Settings::_musicBtnFunction, this);

    _reg.addComponent<eng::Position>(btn, eng::Position(950, 500, 0));
    _reg.addComponent<rtp::Button>(btn, rtp::Button(music, 0, 0, 128 * 4, 32 * 1.5));
    _reg.addComponent<eng::Drawable>(btn, eng::Drawable(_texture.getTextureFromFile("assets/button.png"), 3, {0, 0, 28, 32}));

    float musicVolume = _audio.getMusicVolume(_reg);
    std::stringstream ss;
    ss << musicVolume;
    _reg.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
    _reg.addComponent<eng::Writable>(btntesxt, eng::Writable("MusicButtonText", ss.str(), "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(btntesxt, eng::Position(985, 503, 0));
}

void rtp::Settings::_addMusicText()
{
    eng::Entity text = _reg.spawnEntity();
    int scale = 2;

    _reg.addComponent<eng::Writable>(text, eng::Writable("Text", "Music   :", "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(text, eng::Position(800, 503, 0));
}

int rtp::Settings::_musicBtnFunction()
{
    unsigned int volume = _audio.getMusicVolume(_reg);
    std::stringstream ss;

    auto &texts = _reg.getComponents<eng::Writable>();

    for (int i = 0; i < texts.size(); i++) {
        if (texts[i].has_value() && texts[i].value()._name == "MusicButtonText") {
            if (volume >= 100) {
                texts[i].value()._txt.setString("0");
                _audio.setMusicVolume(_reg, 0);
            }
            else {
                ss << (volume + 10);
                texts[i].value()._txt.setString(ss.str());
                _audio.setMusicVolume(_reg, volume + 10);
            }
        }
    }
    return (0);
}

void rtp::Settings::_addSfxButton()
{
    eng::Entity btn = _reg.spawnEntity();
    eng::Entity btntesxt = _reg.spawnEntity();
    int scale = 2;
    std::function<int()> music = std::bind(&Settings::_sfxBtnFunction, this);

    _reg.addComponent<eng::Position>(btn, eng::Position(950, 600, 0));
    _reg.addComponent<rtp::Button>(btn, rtp::Button(music, 0, 0, 128 * 4, 32 * 1.5));
    _reg.addComponent<eng::Drawable>(btn, eng::Drawable(_texture.getTextureFromFile("assets/button.png"), 3, {0, 0, 28, 32}));

    float musicVolume = _audio.getSfxVolume(_reg);
    std::stringstream ss;
    ss << musicVolume;
    _reg.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
    _reg.addComponent<eng::Writable>(btntesxt, eng::Writable("SfxButtonText", ss.str(), "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(btntesxt, eng::Position(985, 603, 0));
}

void rtp::Settings::_addSfxText()
{
    eng::Entity text = _reg.spawnEntity();
    int scale = 2;

    _reg.addComponent<eng::Writable>(text, eng::Writable("Text", "Sfx   :", "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(text, eng::Position(800, 603, 0));
}

int rtp::Settings::_sfxBtnFunction()
{
    unsigned int volume = _audio.getSfxVolume(_reg);
    std::stringstream ss;

    auto &texts = _reg.getComponents<eng::Writable>();

    for (int i = 0; i < texts.size(); i++) {
        if (texts[i].has_value() && texts[i].value()._name == "SfxButtonText") {
            if (volume >= 100) {
                texts[i].value()._txt.setString("0");
                _audio.setSfxVolume(_reg, 0);
            }
            else {
                ss << (volume + 10);
                texts[i].value()._txt.setString(ss.str());
                _audio.setSfxVolume(_reg, volume + 10);
                _audio.playSound(_reg);
            }
        }
    }
    return (0);
}
