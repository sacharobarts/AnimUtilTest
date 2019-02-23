//
// Copyright (C)  
// 
// File: pluginMain.cpp
//
// Author: Maya Plug-in Wizard 2.0
//

#include <maya/MFnPlugin.h>

#include <maya/MPxFileTranslator.h>

#include <maya/MSelectionList.h>
#include <maya/MGlobal.h>
#include <maya/MAnimUtil.h>
#include <maya/MPlugArray.h>

class AUTest : public MPxFileTranslator {
public:
	AUTest() {}
	~AUTest(){}
	bool haveWriteMethod() const { return true; }
	MString defaultExtension() const { return MString("test"); }
	MStatus writer(const MFileObject& file,
		const MString& optionsString, MPxFileTranslator::FileAccessMode mode) {

		// Debug stuff
		MSelectionList sList;
		MPlugArray aPlugs;
		MGlobal::getActiveSelectionList(sList);
		MGlobal::displayInfo(MString("# selected objects ") + sList.length());
		MGlobal::displayInfo(MString("isAnimated? ") + MAnimUtil::isAnimated(sList));
		MAnimUtil::findAnimatedPlugs(sList, aPlugs);
		MGlobal::displayInfo(MString("number animted plugs: ") + aPlugs.length());

		return MS::kSuccess;
	}
	static void* creator() {

		// Debug stuff
		MSelectionList sList;
		MPlugArray aPlugs;
		MGlobal::getActiveSelectionList(sList);
		MGlobal::displayInfo(MString("# selected objects ") + sList.length());
		MGlobal::displayInfo(MString("isAnimated? ") + MAnimUtil::isAnimated(sList));
		MAnimUtil::findAnimatedPlugs(sList, aPlugs);
		MGlobal::displayInfo(MString("number animted plugs: ") + aPlugs.length());

		return (new AUTest);
	}
};

MStatus
initializePlugin(MObject obj)
{
	MStatus status;
	MFnPlugin plugin(obj, "AnimUtilTest", "0.0");
	status = plugin.registerFileTranslator("AnimUtilTest", "", AUTest::creator);
	return (status);
}

MStatus
uninitializePlugin(MObject obj)
{
	MFnPlugin plugin(obj);
	plugin.deregisterFileTranslator("AnimUtilTest");
	return (MS::kSuccess);
}

