#include "animationComponent.hpp"

cAnimComp::cAnimComp (std::string spriteSheetPath,
		std::string spriteSheetInfoPath): spriteSheet_(nullptr) {
	spriteSheet_ = IMG_Load(spriteSheetPath.c_str());
	if (spriteSheet_ == NULL) {
		std::string errorString = "cAnimComp: Could not load " +
			spriteSheetPath;
		throw std::invalid_argument(errorString);
	}
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError result = xmlDoc.LoadFile(spriteSheetInfoPath.c_str());
	if (result != tinyxml2::XML_SUCCESS) {
		std::string errorString = "cAnimComp: Could not load " +
			spriteSheetInfoPath;
		throw std::invalid_argument(errorString);
	}
	tinyxml2::XMLNode* root = xmlDoc.FirstChild();
	if (root == nullptr) {
		std::string errorString = "cAnimComp: Could not find "
			"Root node in " + spriteSheetInfoPath;
		throw std::runtime_error(errorString);
	}
	tinyxml2::XMLElement* elem = root->FirstChildElement("SheetRoot");
	const char* attrText = nullptr;
	attrText = elem->Attribute("name");
	if (attrText == nullptr) {
		std::string errorString = "cAnimComp: Could not find SheetRoot "
			"node in " + spriteSheetInfoPath;
		throw std::runtime_error(errorString);
	}
	std::string attrStr(attrText);
	// Check attrStr with the name of the file to make sure the correct
	// files are loaded

	// Get the animation info
	tinyxml2::XMLElement* animElem = nullptr;
	animElem = root->FirstChildElement("SheetRoot")->
			   FirstChildElement("Animation");
	if (animElem == nullptr) {
		std::string errorString = "cAnimComp: Could not find Animation "
			"node in " + spriteSheetInfoPath;
		throw std::runtime_error(errorString);
	}
	while (animElem != nullptr) {
		int animId, numFrames;
		tinyxml2::XMLError result;
		result = animElem->QueryIntAttribute("id",&animId);
		if (result != tinyxml2::XML_SUCCESS) {
			std::string errorStr = "cAnimComp: Could not find "
				"animation id attribute in " + spriteSheetInfoPath; 
			throw std::runtime_error(errorStr);
		}
		std::string animationId(attrText);
		result = elem->QueryIntAttribute("numFrames",&numFrames);
		if (result != tinyxml2::XML_SUCCESS) {
			std::string errorStr = "cAnimComp: Could not find "
				"animation numFrames attribute in " + spriteSheetInfoPath; 
			throw std::runtime_error(errorStr);
		}
		result = elem->QueryIntAttribute("fps",&fps_);
		if (result != tinyxml2::XML_SUCCESS) {
			std::string errorStr = "cAnimComp: Could not find "
				"animation fps attribute in " + spriteSheetInfoPath; 
			throw std::runtime_error(errorStr);
		}
		tinyxml2::XMLElement* frameElem = nullptr;
		frameElem = elem->FirstChildElement("Frame");
		if (frameElem == nullptr) {
		}
		std::vector<sFrameInfo> frameList;
		int frameCount = 0;
		// Get frame info
		while (frameElem != nullptr) {
			int frameId;
			result = frameElem->QueryIntAttribute("id",&frameId);
			if (result != tinyxml2::XML_SUCCESS) {
				std::string errorStr = "cAnimComp: Could not find "
					"Frame id attribute in Animation id=" + 
					std::to_string(animId) + "in " + spriteSheetInfoPath;
				throw std::runtime_error(errorStr);
			}
			sFrameInfo tmpFrameInfo;
			tinyxml2::XMLElement* infoElem = nullptr;
			infoElem = frameElem->FirstChildElement("TopLeftX");
			if (infoElem == nullptr) {
				std::string errorString = "cAnimComp: Could not find "
					"topLeftX element in Frame id=" + 
					std::to_string(frameId) + "in " + spriteSheetInfoPath;
				throw std::runtime_error(errorString);
			}
			infoElem->QueryIntText(&tmpFrameInfo.topLeftX);

			infoElem = nullptr;
			infoElem = infoElem->NextSiblingElement("TopLeftY");
			if (infoElem == nullptr) {
				std::string errorString = "cAnimComp: Could not find "
					"topLeftY element in Frame id=" + 
					std::to_string(frameId) + "in " + spriteSheetInfoPath;
				throw std::runtime_error(errorString);
			}
			infoElem->QueryIntText(&tmpFrameInfo.topLeftY);

			infoElem = nullptr;
			infoElem = infoElem->NextSiblingElement("width");
			if (infoElem == nullptr) {
				std::string errorString = "cAnimComp: Could not find "
					"widht element in Frame id=" + 
					std::to_string(frameId) + "in " + spriteSheetInfoPath;
				throw std::runtime_error(errorString);
			}
			infoElem->QueryIntText(&tmpFrameInfo.width);

			infoElem = nullptr;
			infoElem = infoElem->NextSiblingElement("height");
			if (infoElem == nullptr) {
				std::string errorString = "cAnimComp: Could not find "
					"height element in Frame id=" + 
					std::to_string(frameId) + "in " + spriteSheetInfoPath;
				throw std::runtime_error(errorString);
			}
			infoElem->QueryIntText(&tmpFrameInfo.height);

			infoElem = nullptr;
			infoElem = infoElem->NextSiblingElement("dx_centre");
			if (infoElem == nullptr) {
				std::string errorString = "cAnimComp: Could not find "
					"dx_centre element in Frame id=" + 
					std::to_string(frameId) + "in " + spriteSheetInfoPath;
				throw std::runtime_error(errorString);
			}
			infoElem->QueryIntText(&tmpFrameInfo.dx_centre);

			infoElem = nullptr;
			infoElem = infoElem->NextSiblingElement("dy_centre");
			if (infoElem == nullptr) {
				std::string errorString = "cAnimComp: Could not find "
					"dy_centre element in Frame id=" + 
					std::to_string(frameId) + "in " + spriteSheetInfoPath;
				throw std::runtime_error(errorString);
			}
			infoElem->QueryIntText(&tmpFrameInfo.dy_centre);

			frameList.push_back(tmpFrameInfo);
			frameElem = frameElem->NextSiblingElement("Frame");
			++frameCount;
		}
		animElem = animElem->NextSiblingElement("Animation");
		auto mapItr = animMap_.find(animId);
		if (mapItr != animMap_.end()) {
			std::string errorString = "cAnimComp: Animation id " +
				std::to_string(animId) + " already exists in " +
				spriteSheetInfoPath;
			throw std::runtime_error(errorString);
		}
		if (frameCount != numFrames) {
			std::string errorString = "cAnimComp: Number of Frame "
				" elements in Animation id=" + std::to_string(animId) +
				" do not match Animation numFrames=" + 
				std::to_string(numFrames) + "in " + spriteSheetInfoPath;
			throw std::runtime_error(errorString);
		}
		animMap_[animId] = frameList;
	}
}

cAnimComp::~cAnimComp (void) {
	SDL_FreeSurface(spriteSheet_);
	spriteSheet_ = nullptr;
}
