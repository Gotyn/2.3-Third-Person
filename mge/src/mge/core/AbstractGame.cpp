#include "AbstractGame.hpp"

#include <iostream>

#include "mge/core/Input.hpp"
#include "mge/core/Timer.hpp"
#include "mge/core/FPS.hpp"
//#include "mge/core/Renderer.hpp"
#include "mge/core/World.hpp"

using namespace std;

AbstractGame::AbstractGame():_window(NULL),_running(false)
{

}

AbstractGame::~AbstractGame()
{
    //dtor
    delete _window;
//    delete _renderer;
}

void AbstractGame::initialize() {
    cout << "Initializing engine..." << endl << endl;
    _initializeWindow();
    _printVersionInfo();
    _initializeGlew();
    _initializeOpenGL();
    _initializeWorld();
    _initializeScene();
    cout << endl << "Engine initialized." << endl << endl;
}

///SETUP

void AbstractGame::_initializeWindow() {
	cout << "Initializing window..." << endl;
	_window = new sf::RenderWindow( sf::VideoMode(800,600), "My Game!", sf::Style::Default, sf::ContextSettings(24,8,0,3,3));
	_window->setVerticalSyncEnabled(true);
    cout << "Window initialized." << endl << endl;
}

void AbstractGame::_printVersionInfo() {
	cout << "Context info:" << endl;
    cout << "----------------------------------" << endl;
    //print some debug stats for whoever cares
//    const GLubyte *renderer = glGetString( GL_RENDERER );
    const GLubyte *vendor = glGetString( GL_VENDOR );
    const GLubyte *version = glGetString( GL_VERSION );
    const GLubyte *glslVersion = glGetString( GL_SHADING_LANGUAGE_VERSION );
    //nice consistency here in the way OpenGl retrieves values
    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    printf("GL Vendor : %s\n", vendor);
//    printf("GL Renderer : %s\n", renderer);
    printf("GL Version (string) : %s\n", version);
    printf("GL Version (integer) : %d.%d\n", major, minor);
    printf("GLSL Version : %s\n", glslVersion);

    cout << "----------------------------------" << endl << endl;
}

void AbstractGame::_initializeGlew() {
	cout << "Initializing GLEW..." << endl;
    //initialize the opengl extension wrangler
    GLint glewStatus = glewInit();
	cout << "Initialized GLEW, status (1 == OK, 0 == FAILED):" << (glewStatus == GLEW_OK) << endl << endl;
}

void AbstractGame::_initializeOpenGL() {
//    //setup openGL settings
	cout << "Initializing render settings..." << endl;

    glEnable( GL_DEPTH_TEST );
	glEnable( GL_CULL_FACE ); // default GL_BACK
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor((float)0x2d/0xff, (float)0x6b/0xff, (float)0xce/0xff, 1.0f );

    cout << "Render settings loaded." << endl << endl;
}

void AbstractGame::_initializeWorld() {

//    //setup our own renderer
//	cout << "Initializing world..." << endl;
//	_world = new World();
//    cout << "World initialized." << endl << endl;
}

void AbstractGame::_resetWorld() {
//    if (_world != NULL)
//    {
//        delete _world;
//        _world = NULL;
//    }
//    _initializeWorld();
}

///LOOP

void AbstractGame::run()
{
	_running = true;

	while (_running) {
		Timer::update();
		FPS::update();

	    //clear frame, do it here so we can draw debug stuff in any other step etc
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        _update();
        //collision loop over here?
//        _render();

        //swap colorbuffer to screen
        _window->display();

		_processEvents();
	}
}

void AbstractGame::_update() {
    World::Instance()->update(Timer::deltaTime(), glm::mat4());
}

//void AbstractGame::_render () {
////    _renderer->render(World::Instance());
//}

void AbstractGame::_processEvents()
{
	sf::Event event;
	bool exit = false;

    //clear keyDown array
    for (unsigned int i=0; i<sizeof(Input::_keyDown); i++)
    {
        Input::_keyDown[i] = false;
    }

	//we must empty the event queue
	while( _window->pollEvent( event ) ) {
        //give all system event listeners a chance to handle events
        //optionally to be implemented by you...
        //SystemEventDispatcher::dispatchEvent(event);

        switch (event.type) {
            case sf::Event::Closed:
                exit = true;
                break;
            case sf::Event::KeyPressed:
                //enter value to that array here
                if (event.key.code == sf::Keyboard::Escape) {
                    exit = true;
                }

                Input::_keyDown[event.key.code] = true;
                break;
            case sf::Event::KeyReleased:
                break;
            case sf::Event::Resized:
                //would be better to move this to the renderer
                //this version implements nonconstrained match viewport scaling
                glViewport(0, 0, event.size.width, event.size.height);
                break;

            default:
                break;
        }
	}

	if (exit) {
        _window->close();
        _running = false;
	}
}



