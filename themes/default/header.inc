<html>
<head>
<title><?php echo $project['title']; ?></title>
<link class="common" href="themes/default/default.css" rel="stylesheet" type="text/css" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"></head>
<body >
<div class='common_all'>
<div class='common_top'>
		<span class="common_logo"><img src="<?php echo $project['logo']; ?>" width="116" height="89"></span>
    <h3 align="center" class="common_header"><center>
    <?php echo $project['heading']; ?></span> </center></h3>
</div>
                        <div class='common_left' width=135>
<?php echo theme_default_menu_beautifier($project['menu']); ?>
                        </div>
												<div class='common_center'>


