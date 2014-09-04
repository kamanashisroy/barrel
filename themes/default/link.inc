<?php

function theme_render_link($link) {
	return '<a href="'.$link['link'].'">'.$link['title'].'</a>';
}
