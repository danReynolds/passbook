// Tabbed Pane project template
import bb.cascades 1.0

TabbedPane {
    showTabsOnActionBar: true
    id:root
    Tab {
        title: qsTr("Home")
         imageSource:"asset:///images/homeIcon.png"
        Page {
            id: tab1
            actions: [
                // define the actions for first tab here
                ActionItem {
                    title: qsTr("View Grades")
                    onTriggered: {
                        root.activePane=grades;
                        root.activeTab=gradesTab;
                    }
                }
            ]
            Container {
                // define tab content here
                layout: AbsoluteLayout {}
                ImageView {
                    id:background
                    preferredHeight:1280 
                    preferredWidth:768
                    imageSource: "asset:///images/homeBackground2.jpg"
                }
            }
        }
    }
    Tab {
        id:gradesTab
        title: qsTr("Grades")
        imageSource:"asset:///images/gradesIcon.png"
        GradeList {
            id:grades
        }
    }

    onCreationCompleted: {
        // this slot is called when declarative scene is created
        // write post creation initialization here
        console.log("TabbedPane - onCreationCompleted()")

        // enable layout to adapt to the device rotation
        // don't forget to enable screen rotation in bar-bescriptor.xml (Application->Orientation->Auto-orient)
        OrientationSupport.supportedDisplayOrientation = SupportedDisplayOrientation.All;
    }
}
