

                </div>
</div>
<?php if(!is_null($project["contact"])) { ?>
<span class="style2"><a href=<?php echo '\"' . $project["contact"] . '\"'; ?>>Contact Us</a></span>
<?php } ?>
<?php if(!is_null($project["company"])) { ?>
<span class="style2">&copy; <?php echo $project["company"]; ?>, All rights reserved.</span>
<?php } ?>
</body>
</html>
