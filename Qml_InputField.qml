import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Flickable {
	id: flick
	property string mytext: "Unknown"

	anchors.fill: parent
	clip: true

	function ensureVisible(r)
	{
		if (contentX >= r.x)
			contentX = r.x;
		else if (contentX+width <= r.x+r.width)
			contentX = r.x+r.width-width;
		if (contentY >= r.y)
			contentY = r.y;
		else if (contentY+height <= r.y+r.height)
			contentY = r.y+r.height-height;
	}

	TextEdit {
		id: edit
		focus: true
		wrapMode: TextEdit.Wrap
		onCursorRectangleChanged: flick.ensureVisible(cursorRectangle)

		anchors.fill: parent
		text: mytext
		verticalAlignment: TextInput.AlignVCenter
		horizontalAlignment: TextInput.AlignHCenter

		onTextChanged: {
			mytext = text
		}
	}
}
