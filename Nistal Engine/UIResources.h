#include "Globals.h"
#include "UIWindow.h"

#include <vector>


class UIResources : public UIWindow
{
public:
	UIResources();
	~UIResources();


	bool Start();
	void Draw();
	bool CleanUp();
	void SetHierarchy(GameObject* root);
	void SetPos();

private:
	uint counter = -1;

};

#endif 
