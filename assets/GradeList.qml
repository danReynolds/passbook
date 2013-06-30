import bb.cascades 1.0
import bb.system 1.0
Page {
    resizeBehavior: PageResizeBehavior.None 
    property variant contentView
    property string display
    property int active:0
    actions: [
        ActionItem {
            ActionBar.placement: ActionBarPlacement.InOverflow
            imageSource: "asset:///images/recordIcon.png"
            title: "New Mark"
            onTriggered: {
                addGrade.open();
            }
        }
    ]
    function clear() {
        description.text="";
        classes.text="";
        weighting.text="";
        grade.text="";
        title.text="";
        info.translationX=999;
    }
    function setInfo() {
        titleReview.text=contextProperty.getValueFor("classes","");
        classesReview.text=contextProperty.getValueFor("title","");
        descriptionReview.text=contextProperty.getValueFor("description","");
        mark.text=contextProperty.getValueFor("marks","")+"%";
        weight.text=contextProperty.getValueFor("weighting","")+"%";
    }
    id: grades
    titleBar: TitleBar {
        title:"Class Marks"
        id:titleBar
    }
    attachedObjects: [
            SystemToast {
               id: toastHello
               body:"hey"
               button.label: "hey"
               position: SystemUiPosition.BottomCenter
             
            },
        Sheet {
            id: addGrade
            peekEnabled:true
            content: Page {
                resizeBehavior: PageResizeBehavior.None 
                titleBar: TitleBar {
                    id: create
                    title: "New Mark"
                    visibility: ChromeVisibility.Overlay
                    dismissAction: ActionItem {
                        title: "Cancel"
                        onTriggered: {
                            
                            addGrade.close();
                            grades.clear();
                        
                        }
                    }
                    acceptAction: ActionItem {
                        title: "Submit"
                        onTriggered: {
                            if (title.text.length>0 && classes.text.length>0) {
                                contextProperty.addNewRecord(title.text,classes.text,description.text, grade.text,weighting.text);
                                active=0;
                                addGrade.close();
                                grades.clear();
                            }
                            else {
                                title.hintText="Enter a Title";
                                classes.hintText="Enter a Class";
                                }
                        }
                    }
                }
                
                Container {
                    translationY:0
                    preferredHeight:1280
                    preferredWidth:768
                    background: Color.create("#E0F2F7")
                    layoutProperties: StackLayoutProperties {
                    }
                    verticalAlignment: VerticalAlignment.Center
                    horizontalAlignment: HorizontalAlignment.Center
                    
                    TextArea {
                        translationY:200
                        preferredHeight:120
                        preferredWidth:650
                        id:title
                        hintText: "Title"
                        verticalAlignment: VerticalAlignment.Top
                        horizontalAlignment: HorizontalAlignment.Center
                    }
                    TextArea {
                        translationY:240
                        preferredHeight: 120
                        preferredWidth:650
                        id: classes
                        hintText:"Class"
                        verticalAlignment: VerticalAlignment.Top
                        horizontalAlignment: HorizontalAlignment.Center
                    }
                    TextArea {
                        id: description
                        translationY:280
                        hintText: "Notes"
                        preferredHeight:250
                        preferredWidth:650
                        verticalAlignment: VerticalAlignment.Top
                        horizontalAlignment: HorizontalAlignment.Center
                    }
                    Container {
                        translationY:300
                        preferredWidth:768
                        preferredHeight:110
                        TextArea {
                            id:grade
                            hintText:"Grade(%)"
                            preferredWidth:250
                            preferredHeight:100
                            translationX:468
                            translationY:12
                        }
                        TextArea {
                            id: weighting
                            translationY:-100
                            preferredWidth:250
                            preferredHeight:100
                            hintText:"Weight(%)"
                            translationX:60
                        }
                    }
                    ImageView {
                        translationY:85
                        translationX:20
                        id:marks
                        imageSource:"asset:///images/1355511586_book_blue.png"
                        horizontalAlignment: HorizontalAlignment.Center
                        scaleX:0.7
                        scaleY:0.7
                    }
                
                }
            }
        },
        Sheet {
            id:reviewPage
            content: Page {
                titleBar: TitleBar {
                    id: reviewTitle
                    title: "Marks"
                    visibility: ChromeVisibility.Overlay
                    dismissAction: ActionItem {
                        title: "Cancel"
                        onTriggered: {
                            if (active){
                                info.translationX=800;
                                active=0;
                            }
                            else {
                                reviewPage.close();
                                grades.clear();
                                }
                        }
                    }
                    acceptAction: ActionItem {
                        title: "Submit"
                        onTriggered: {
                            active=0;
                            contextProperty.updateSelectedRecord(titleReview.text,classesReview.text,descriptionReview.text, contextProperty.getValueFor("marks",""),contextProperty.getValueFor("weighting",""));
                            reviewPage.close();
                            grades.clear();
                        }
                    }
                }
                Container {
                    
                    layout: AbsoluteLayout{}
                    background: Color.create("#E0F2F7")
                    Label {
                        text:"Title:"
                        id:titleLabel
                        translationX:50
                        translationY:200
                    }
                    TextArea {
                        translationX:50
                        translationY:275
                        preferredHeight:120
                        preferredWidth:650
                        id:titleReview
                        text: contextProperty.getValueFor("title","");
                        verticalAlignment: VerticalAlignment.Top
                        horizontalAlignment: HorizontalAlignment.Center
                    }
                    Label {
                        id:classLabel
                        text:"Class:"
                        translationX:50
                        translationY:405
                    }
                    TextArea {
                        translationY:475
                        translationX:50
                        preferredHeight: 120
                        preferredWidth:650
                        id: classesReview
                        text:contextProperty.getValueFor("classes","");
                        verticalAlignment: VerticalAlignment.Top
                        horizontalAlignment: HorizontalAlignment.Center
                    }
                    TextArea {
                        id: descriptionReview
                        translationY:700
                        translationX:50
                        text: contextProperty.getValueFor("description","");
                        preferredHeight:250
                        preferredWidth:650
                        verticalAlignment: VerticalAlignment.Top
                        horizontalAlignment: HorizontalAlignment.Center
                    }
                    Label  {
                        text: "Mark:"
                        translationY:1000
                        translationX:50
                    }
                    
                    Label {
                        id:mark
                        translationY:1050
                        translationX:85
                        text: contextProperty.getValueFor("marks","") + "%"
                        textStyle.fontSizeValue: 60.0
                    }
                    Label  {
                        text: "Weight:"
                        translationY:1100
                        translationX:50
                    }
                    
                    Label {
                        id:weight
                        translationY:1150
                        translationX:85
                        text: contextProperty.getValueFor("weighting","") + "%"
                        textStyle.fontSizeValue: 60.0
                    }
                    
                    Button {
                        id:details
                        text:"Class Info"
                        translationY:1000
                        translationX:350
                        onClicked: {
                            info.translationX=0;
                            active=1;
                            current.text="Class: " + contextProperty.getValueFor("title","");
                            displayed.text=""+contextProperty.countGrades(contextProperty.getValueFor("title",""),3);
                            choices.selectedIndex=0;
                        }
                    }
                    Button {
                        id:erase
                        translationY:1120
                        translationX:350
                        text: "Erase Mark"
                        attachedObjects: [
                            SystemDialog {
                                id: myQmlDialog
                                title: "Confirm Delete"
                                body: "Would you really like to delete this mark?"
                                onFinished:{
                                    if (myQmlDialog.result ==3) {
                                    }
                                    if (myQmlDialog.result==2) {
                                        contextProperty.deleteRecord();
                                        reviewPage.close();
                                        toastHello.show();
                                    }
                                } 
                            }
                        ]
                        onClicked: {
                            myQmlDialog.show()
                        }
                    }
                    Container {
                        id:info
                        preferredWidth:768
                        preferredHeight:1280
                        translationX:1000
                        translationY:20
                        background: Color.create("#E0F2F7")
                        layout: AbsoluteLayout{}
                        Label {
                            id:stats
                            text:"Grade Information" 
                            translationX:50
                            translationY:150
                        }
                        Label {
                            id: current
                            text: "Class:"
                            translationX:50
                            translationY:200
                        }
                        Label {
                            id:displayed
                            text:""
                            layoutProperties: AbsoluteLayoutProperties {
                                positionX:350
                                positionY:600
                            }
                            textStyle {
                                base: SystemDefaults.TextStyles.BigText
                                color: Color.create(0.1, 0.4, 0.8)
                                fontStyle: FontStyle.Italic
                            }
                        }
                        DropDown {
                            layoutProperties: AbsoluteLayoutProperties {
                                positionX:75
                                positionY:400
                            }
                            preferredWidth:600
                            id:choices
                            Option {
                                text: "Weighted Average"
                                selected: true
                            }
                            Option {
                                text: "Percent Earned to Date"
                            }
                            Option {
                                text: "Highest Achievable Mark"
                            }
                            onSelectedIndexChanged: {
                                if (selectedIndex == 0) {
                                    displayed.text=""+contextProperty.countGrades(contextProperty.getValueFor("title",""),3);
                                } else if (selectedIndex == 1) {
                                    displayed.text=""+contextProperty.countGrades(contextProperty.getValueFor("title",""),2);
                                } else if (selectedIndex== 2) {
                                    displayed.text=""+contextProperty.countGrades(contextProperty.getValueFor("title",""),1);
                                } 
                            }
                        }
                        
                        Label {
                            id:more
                            text:"More Features                                Coming Soon!"
                            multiline:true
                            layoutProperties: AbsoluteLayoutProperties {
                                positionX:100
                                positionY:800
                            }
                            textStyle {
                                base: SystemDefaults.TextStyles.BigText
                                color: Color.create(0.1, 0.4, 0.8)
                            
                            }
                        }
                    }
                
                }
            }
        }
    ]
    Container {
        background: Color.create("#E0F2F7")
        id:empty
        layout: StackLayout {
        }
        TextArea {
            hintText: "Search..."
            translationY:10
            id:searchBar
            onTextChanging: {
                songsList.resetDataModel();
                contextProperty.setClass(searchBar.text);
                songsList.setDataModel(songsModel);
            }
        }
        ListView {
            translationY:0
            translationX:0
            objectName: "songsList"
            id: songsList
            preferredHeight:850
            
            dataModel: songsModel // XmlDataModel {source:"weather.xml"}
            listItemComponents: [ //set the items in the list, one item for each song and headers.
                ListItemComponent {
                    type: "item"
                    StandardListItem {
                        imageSpaceReserved: false
                        title: ListItemData.classes
                        status: ListItemData.marks+"%"
                    }
                },
                ListItemComponent {
                    type: "header"
                    Header {
                        title: ListItemData
                        subtitle:ListItemData.classes
                    }
                }
            ]
            onTriggered: {
                songsList.clearSelection();
                select(indexPath);
                contextProperty.findIndexPath(indexPath);
                contextProperty.saveValueFor("title",contentView.title);
                contextProperty.saveValueFor("classes",contentView.classes);
                contextProperty.saveValueFor("description",contentView.description);
                contextProperty.saveValueFor("marks",contentView.marks);
                contextProperty.saveValueFor("weighting",contentView.weighting);
                grades.setInfo();
                reviewPage.open();
            
            }
            onSelectionChanged: {
                if (selected) {
                    var chosenItem = dataModel.data(indexPath);
                    contentView = chosenItem;
                }
            }
            layoutProperties: StackLayoutProperties {
                spaceQuota: -1.0
            }
        }
        ImageView {
            
            imageSource:"asset:///images/addButton.png"
            id:imageName
            onTouch: {
                if (event.isDown()) {
                    addGrade.open();
                }
            }
            scaleY:0.6
            scaleX:0.3
            horizontalAlignment: HorizontalAlignment.Center
            verticalAlignment: VerticalAlignment.Bottom
            layoutProperties: StackLayoutProperties {
                spaceQuota: -1.0
            }
        }
        Label {
            id:labelName
            
            translationY:-20
            text:"Add your Marks"
            
            horizontalAlignment: HorizontalAlignment.Center
        }
    }

}
