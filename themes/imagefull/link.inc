<?php

function theme_render_link($link) {
	return '<a href="'.$link['link'].'">'.$link['title'].'</a>';
}


function theme_render_image($img) {
	return '<img width=128 height=128 src="'.$img['src'].'"></img>';
}
