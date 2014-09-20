window.onload = function () {
	//var tree = document.getElementById("barrel_menu");
	var tree = document.getElementById("barrel_menu_tree");
	var lists = [ tree ];

	for (var i = 0; i < tree.getElementsByTagName("ul").length; i++)
		lists[lists.length] = tree.getElementsByTagName("ul")[i];
	for (var i = 0; i < lists.length; i++) {
		var item = lists[i].lastChild;
		var wrapped = true;
		while (item.previousSibling/*!item.tagName/* || item.tagName.toLowerCase() == "li"*/) {
			if(item.className == 'barrel_current_page') {
				wrapped = false;
				break;
			}
			item = item.previousSibling;
		}
		if(wrapped) {
			lists[i].className += " wrapped";
		}
	}
};

function unwrap(item) {
	if(item.className.indexOf("wrapped") != -1) {
		item.className = item.className.replace(" wrapped","");
	} else {
		item.className += " wrapped";
	}
	return true;
}
