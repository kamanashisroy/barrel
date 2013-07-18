
campaign:
	echo "get campaign campaign 11\nq" | ./playtool
	echo "campaign_job" | ./playtool

db_get_test:
	echo "get test mango 1\nq" | ./playtool

db_insert_test:
	echo "insert test mango ( name => jelly )\nq" | ./playtool
	
user_create:
	echo "user_create ( username => admin password => 13456 )\nq" | ./playtool
	echo "get campaign user 1\nq" | ./playtool

user_get:
	echo "get campaign user 1\nq" | ./playtool

