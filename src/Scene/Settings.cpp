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
    _addBackgrounds();
    _addTitle();
    _addFrameRateButton();
    _addFrameRateText();
    _addMusicButton();
    _addMusicText();
    _addMusic();
    _addSfxButton();
    _addSfxText();
    _addSfx();
    _addButtonMainMenu();
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

void rtp::Settings::_addBackgrounds()
{
    for (int i = 0; i < 10; i++) {
        eng::Entity bg = _reg.spawnEntity();
        if (i >= 0 && i < 2) {
            _reg.addComponent<eng::Position>(bg, eng::Position((i % 2) * 1920, 0, 10));
            _reg.addComponent<eng::Drawable>(bg, eng::Drawable(_texture.getTextureFromFile("assets/background.png")));
            _reg.addComponent<rtp::Background>(bg, rtp::Background());
        } if (i >= 2 && i < 4) {
            _reg.addComponent<eng::Position>(bg, eng::Position((i % 2) * 1920, 0, 9));
            _reg.addComponent<eng::Velocity>(bg, eng::Velocity(-100, 0));
            _reg.addComponent<eng::Drawable>(bg, eng::Drawable(_texture.getTextureFromFile("assets/fog1.png")));
            _reg.addComponent<rtp::Background>(bg, rtp::Background());
        } if (i >= 4 && i < 6) {
            _reg.addComponent<eng::Position>(bg, eng::Position((i % 2) * 1920, 0, 8));
            _reg.addComponent<eng::Velocity>(bg, eng::Velocity(-200, 0));
            _reg.addComponent<eng::Drawable>(bg, eng::Drawable(_texture.getTextureFromFile("assets/stars1.png")));
            _reg.addComponent<rtp::Background>(bg, rtp::Background());
        }
    }
}

void rtp::Settings::_addTitle()
{
    eng::Entity text = _reg.spawnEntity();
    int scale = 5;

    _reg.addComponent<eng::Writable>(text, eng::Writable("Title", "Settings", "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(text, eng::Position(890, 200, 0));
}

void rtp::Settings::_addFrameRateButton()
{
    eng::Entity btn = _reg.spawnEntity();
    eng::Entity btntesxt = _reg.spawnEntity();
    int scale = 2;
    std::function<int()> frameRate = std::bind(&Settings::_frameRateBtnFunction, this);

    _reg.addComponent<eng::Position>(btn, eng::Position(980, 400, 0));
    _reg.addComponent<rtp::Button>(btn, rtp::Button(frameRate, 0, 0, 128 * 4, 32 * 1.5));
    _reg.addComponent<eng::Drawable>(btn, eng::Drawable(_texture.getTextureFromFile("assets/button.png"), 3, {0, 0, 28, 32}));

    unsigned int fpsValue = _graphic.getFrameRateLimit();
    std::stringstream ss;
    ss << fpsValue;
    _reg.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
    _reg.addComponent<eng::Writable>(btntesxt, eng::Writable("FPSButtonText", ss.str(), "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(btntesxt, eng::Position(1015, 403, 0));
}

void rtp::Settings::_addFrameRateText()
{
    eng::Entity text = _reg.spawnEntity();
    int scale = 2;

    _reg.addComponent<eng::Writable>(text, eng::Writable("FPSText", "FPS   :", "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(text, eng::Position(830, 403, 0));
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

    _reg.addComponent<eng::Position>(btn, eng::Position(980, 500, 0));
    _reg.addComponent<rtp::Button>(btn, rtp::Button(music, 0, 0, 128 * 4, 32 * 1.5));
    _reg.addComponent<eng::Drawable>(btn, eng::Drawable(_texture.getTextureFromFile("assets/button.png"), 3, {0, 0, 28, 32}));

    float musicVolume = _audio.getMusicVolume(_reg);
    std::stringstream ss;
    ss << musicVolume;
    _reg.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
    _reg.addComponent<eng::Writable>(btntesxt, eng::Writable("MusicButtonText", ss.str(), "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(btntesxt, eng::Position(1015, 503, 0));
}

void rtp::Settings::_addMusicText()
{
    eng::Entity text = _reg.spawnEntity();
    int scale = 2;

    _reg.addComponent<eng::Writable>(text, eng::Writable("Text", "Music   :", "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(text, eng::Position(830, 503, 0));
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

    _reg.addComponent<eng::Position>(btn, eng::Position(980, 600, 0));
    _reg.addComponent<rtp::Button>(btn, rtp::Button(music, 0, 0, 128 * 4, 32 * 1.5));
    _reg.addComponent<eng::Drawable>(btn, eng::Drawable(_texture.getTextureFromFile("assets/button.png"), 3, {0, 0, 28, 32}));

    float musicVolume = _audio.getSfxVolume(_reg);
    std::stringstream ss;
    ss << musicVolume;
    _reg.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
    _reg.addComponent<eng::Writable>(btntesxt, eng::Writable("SfxButtonText", ss.str(), "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(btntesxt, eng::Position(1015, 603, 0));
}

void rtp::Settings::_addSfxText()
{
    eng::Entity text = _reg.spawnEntity();
    int scale = 2;

    _reg.addComponent<eng::Writable>(text, eng::Writable("Text", "Sfx   :", "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(text, eng::Position(830, 603, 0));
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

void rtp::Settings::_addButtonMainMenu()
{
    eng::Entity btn = _reg.spawnEntity();
    eng::Entity btntesxt = _reg.spawnEntity();
    int scale = 4;

    std::function<int()> menu = std::bind(&Settings::_mainMenuBtnFunction, this);
    _reg.addComponent<eng::Position>(btn, eng::Position(842, 700, 0));
    _reg.addComponent<rtp::Button>(btn, rtp::Button(menu, 0, 0, 128 * 1.9, 32 * 1.5));
    _reg.addComponent<eng::Drawable>(btn, eng::Drawable(_texture.getTextureFromFile("assets/button.png"), 3, {0, 0, 128, 32}));
    _reg.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(1.9, 1.5);
    _reg.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Return", "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(btntesxt, eng::Position(917, 703, 0));
}

int rtp::Settings::_mainMenuBtnFunction()
{
    _sceneEvent = 1;
    return 0;
}