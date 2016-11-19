#include "Activity.h"
#include "GameLayer.h"
#include "DebugLayer.h"

int main()
{
	Activity activity;
	activity.addLayer(new GameLayer(sf::FloatRect(0, 0, 800, 400)));
	activity.start();

    return 0;
}