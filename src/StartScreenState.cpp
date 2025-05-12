#include "header.h"
#include "StartScreenState.h"
#include "SpaceInvadersEngine.h"
#include "StateSystem.h"
#include "StartGameButton.h"
#include "PlayerShip.h"
#include "Projectile.h"
#include "PixelTileManager.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "PlayGameState.h"
#include "TextFieldButton.h"
#include "TextBoxButton.h"
#include <fstream>

#include "PerlinNoise.h"
#include "Utility.h"

//UTILITY FUNCTIONS

//interpolate between 2 colours
//from : https://stackoverflow.com/questions/13488957/interpolate-from-one-color-to-another
int calculateInterpolatedColour(int color1, int color2, float fraction)
{
	unsigned char   r1 = (color1 >> 16) & 0xff;
	unsigned char   r2 = (color2 >> 16) & 0xff;
	unsigned char   g1 = (color1 >> 8) & 0xff;
	unsigned char   g2 = (color2 >> 8) & 0xff;
	unsigned char   b1 = color1 & 0xff;
	unsigned char   b2 = color2 & 0xff;

	return (int)((r2 - r1) * fraction + r1) << 16 |
		(int)((g2 - g1) * fraction + g1) << 8 |
		(int)((b2 - b1) * fraction + b1);
}

StartScreenState::StartScreenState(SpaceInvadersEngine* engine, StateSystem* stateSystem) 
	: State(engine, stateSystem),
	iCurrentDrawingSurface(0)
{
	//Handle surfaces
	NUMBER_OF_SURFACES = 10;
	//Backup the original to restore 
	pOriginalSurfaceBackup = m_pEngine->getBackgroundSurface(); //warning: surface not initialised for the back up
	for (int i = 0; i < NUMBER_OF_SURFACES; i++) {
		vecDrawingSurfaces.push_back(DrawingSurface(m_pEngine));
	}

}

StartScreenState::~StartScreenState()
{
	//Restore the background surface
	//m_pEngine->setBackgroundSurface(pOriginalSurfaceBackup);

	//delete pOriginalSurfaceBackup;
	//delete m_pEngine->getForegroundSurface();

	//std::cout << "CALLING START SCREEN STATE DESTRUCTOR" << std::endl;
	
}


void StartScreenState::renderCurrentBackgroundSurface(double zNoise, int starSize, double starRotation) {
	//Fill with 0x161B2C dark blue
	int BACKGROUND_COLOUR = 0x161B2C;
	m_pEngine->fillBackground(BACKGROUND_COLOUR);

	srand(50);

	int HEIGHT = m_pEngine->getWindowHeight();
	int WIDTH = m_pEngine->getWindowWidth();
	PerlinNoise pn;
	SimpleImage star = ImageManager::loadImage("resources/SpaceShooterRedux/PNG/Effects/star1.png", true);

	//Add a bit of noise
	for (int iX = 0; iX < WIDTH; iX++) {
		for (int iY = 0; iY < HEIGHT; iY++) {
			int col = ((rand() % 100)) / 100.0 * (0xff0000) +
				((rand() % 100)) / 100.0 * (0x00ff00) +
				((rand() % 100)) / 100.0 * (0x0000ff);

			
			//Apply thick noise
			if (rand() % 1000 <= 300) {
				int transparentColour = calculateInterpolatedColour(col, BACKGROUND_COLOUR, 0.85);
				m_pEngine->setBackgroundPixel(iX, iY, transparentColour);
			}
			
			//Apply fine noise
			if (rand() % 1000 <= 30) {
				int transparentColour = calculateInterpolatedColour(col, BACKGROUND_COLOUR, rand() % 5 / 5.0);
				m_pEngine->setBackgroundPixel(iX, iY, transparentColour);
			}

			//Apply perlin noise
			double resolution = 70;
			double xNoise = iX / resolution + zNoise;
			double yNoise = iY / resolution;

			if (rand() % 1000 <= 100) {
				double noiseValue = pn.noise(xNoise, yNoise, zNoise);
				m_pEngine->setBackgroundPixel(iX, iY,
					calculateInterpolatedColour(col, BACKGROUND_COLOUR, noiseValue));
			}
			
		}
	}

	//Also render some nice stars
	srand(555);
	int STARS_COUNT = 11;
	for (int i = 0; i < STARS_COUNT; i++) {
		Utility::renderScaledImageWithMask(
			m_pEngine, m_pEngine->getBackgroundSurface(),
			star,
			rand() % WIDTH, rand() % HEIGHT,
			starSize, starSize, starRotation);
	}

	srand(1);
}

//Called by some higher objects
void StartScreenState::createSurfaces()
{
	//Basic surfaces
	m_pEngine->BaseEngine::virtCreateSurfaces();

	//Extra Background surfaces
	for (int i = 0; i < NUMBER_OF_SURFACES; i++) {
		vecDrawingSurfaces[i].createSurface(m_pEngine->getWindowWidth(), m_pEngine->getWindowHeight());
	}
}

int StartScreenState::initialiseObjects()
{
	m_pEngine->drawableObjectsChanged();

	m_pEngine->destroyOldObjects(true);

	m_pEngine->createObjectArray(5);

	//Create the player ship
	SimpleImage playerTexture = ImageManager::loadImage("resources/SpaceShooterRedux/PNG/playerShip1_blue.png");
	PlayerShip* playerShip = new PlayerShip(m_pEngine, playerTexture, playerTexture.getWidth(), playerTexture.getHeight());
	m_pEngine->storeObjectInArray(0, playerShip);

	//Create the button and store it
	int startButtonWidth = 400;
	int startButtonHeight = 70;
	StartGameButton* startGameButton = new StartGameButton(m_pEngine, startButtonWidth, startButtonHeight);
	startGameButton->setPosition(
		m_pEngine->getWindowWidth()/2 - startButtonWidth/2, 
		m_pEngine->getWindowHeight()/2 - startButtonHeight/2); //middle
	m_pEngine->storeObjectInArray(1, startGameButton);

	//Add dummy enemy
	Enemy* enemy = EnemyManager::createEnemy(m_pEngine, BASIC_ENEMY, 100, 100);
	m_pEngine->storeObjectInArray(2, enemy);

	//Add text field
	int textFieldWidth = 300;
	int textFieldHeight = 24;
	TextFieldButton* textField = new TextFieldButton(m_pEngine, textFieldWidth, textFieldHeight);
	textField->setPosition(m_pEngine->getWindowWidth() - textFieldWidth - 20, textFieldHeight);
	m_pEngine->storeObjectInArray(3, textField);

	//Add text box
	int textBoxWidth = 300;
	int textBoxInitialHeight = 24;
	TextBoxButton* textBox = new TextBoxButton(m_pEngine, textBoxWidth, textBoxInitialHeight);
	textBox->setPosition(m_pEngine->getWindowWidth() - textBoxWidth - 20, textBoxInitialHeight + textFieldHeight + 24);
	textBox->updateTextFromFile("resources/highscores.txt");
	m_pEngine->storeObjectInArray(4, textBox);

	m_pEngine->setAllObjectsVisible(true);

	return 0;
}

void StartScreenState::mainLoopDoAfterUpdate()
{
	//Destroy required projectiles
	DisplayableObject* pObject = NULL;
	for (int objID = 0; (pObject = m_pEngine->getDisplayableObject(objID)) != NULL; objID++) {
		pObject = dynamic_cast<Projectile*>(pObject);
		if (pObject) {
			//object is a projectile
			if (((Projectile*)pObject)->toBeRemoved() || ((Projectile*)pObject)->hasHit()) {
				//std::cout << "Projectile Removed and deleted;" << std::endl;
				m_pEngine->removeDisplayableObject(pObject);
				delete pObject;
			}
		}
	}

}


PixelTileManager* StartScreenState::getTileManager()
{
	return nullptr;
}

void StartScreenState::setupBackgroundBuffer()
{
	double baseZNoise = 0.1;
	double multiplierNoise = 1.5;
	double baseStarSize = 15;
	double starSizeOffset = 25;

	for (int i = 0; i < NUMBER_OF_SURFACES; i++) {

		double oscillatingValue = abs(i - NUMBER_OF_SURFACES / 2.0);
		//Max Star size -> 40
		//Min Star size -> 20
		double starSize = (-starSizeOffset * 4 / (NUMBER_OF_SURFACES * NUMBER_OF_SURFACES)) * oscillatingValue * oscillatingValue + starSizeOffset + baseStarSize;
		std::cout << "Star Size: " << starSize << std::endl;	
		m_pEngine->setBackgroundSurface(&vecDrawingSurfaces[i]);
		vecDrawingSurfaces[i].mySDLLockSurface();
		renderCurrentBackgroundSurface(
			baseZNoise * multiplierNoise * oscillatingValue,
			starSize,
			i * (360 / NUMBER_OF_SURFACES));
		vecDrawingSurfaces[i].mySDLUnlockSurface();
	}
	m_pEngine->setBackgroundSurface(&vecDrawingSurfaces[0]);
}

void StartScreenState::mainLoopPreUpdate()
{
	//Handles background animation rotation
	int currentTime = m_pEngine->getModifiedTime();
	if (currentTime - lastChangedTime > 100) {
		//std::cout << "Surface: " << iCurrentDrawingSurface << std::endl;
		iCurrentDrawingSurface = (iCurrentDrawingSurface + 1) % NUMBER_OF_SURFACES;
		m_pEngine->setBackgroundSurface(&vecDrawingSurfaces[iCurrentDrawingSurface]);
		lastChangedTime = currentTime;
	}

	m_pEngine->redrawDisplay();
}



void StartScreenState::handleMouseDown(int iButton, int iX, int iY)
{

	TextFieldButton* textFieldButton = (TextFieldButton*)m_pEngine->getDisplayableObject(3);
	if (textFieldButton->virtIsPositionWithinObject(iX, iY)) {
		textFieldButton->isClicked = true;
	}
	else {
		textFieldButton->isClicked = false;
	}



	StartGameButton* startGameButton = (StartGameButton*)m_pEngine->getDisplayableObject(1);
	if (startGameButton->virtIsPositionWithinObject(iX, iY)) {
		//Restore original background pointer first
		m_pEngine->setBackgroundSurface(pOriginalSurfaceBackup);
		//Set the new state
		m_pStateSystem->setState(new PlayGameState(m_pEngine, m_pStateSystem));
	}
}


void StartScreenState::keyDown(int iKeyCode)
{
	TextFieldButton* textFieldButton = (TextFieldButton*)m_pEngine->getDisplayableObject(3);
	if (textFieldButton->isClicked) {
		if (((iKeyCode >= 48 && iKeyCode <= 57) || (iKeyCode >= 97 && iKeyCode <= 122))) {
			textFieldButton->addCharacter(iKeyCode);
		}
		else if (iKeyCode == 8) {
			//backspace
			textFieldButton->deleteLastCharacter();
		}
		else if (iKeyCode == 13) {
			//flush text to file
			std::ofstream file;
			file.open("resources/highscores.txt", std::ios_base::app);
			if (file.is_open()) {
				if (textFieldButton->getText().size() > 0) {
					file << textFieldButton->getText() << std::endl;
					std::cout << "Written to file" << std::endl;
				}
				file.close();
				textFieldButton->eraseText();
			}
			else {
				std::cout << "ERROR: Could not open highscores file." << std::endl;
			}

			//also read from file and update display...
			TextBoxButton* textBoxButton = (TextBoxButton*)m_pEngine->getDisplayableObject(4);
			textBoxButton->updateTextFromFile("resources/highscores.txt");
		}

	}

	//std::cout << "key: " << iKeyCode << std::endl;
}