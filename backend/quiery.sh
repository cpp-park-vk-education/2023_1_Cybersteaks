# project api demonstration(sample)

curl -X POST localhost:1026/account/signup -H "Content-Type: application/json" -d ''
# {"message":"body is required","status":"error"}

printf '\n'

curl -X POST localhost:1026/account/signup -H "Content-Type: application/json" -d '{"login": 7}'
# {"message":"missing login/email/password","status":"error"}

printf '\n'

curl -X POST localhost:1026/account/signup -H "Content-Type: application/json" -d '{"login":"jack", "email":"j123@yandex.ru", "password":"pass", "repeated password":"pass"}'
# {"creation_date":"2023-05-25 13:23:25.367771","email":"antonybill@gmail.com","message":"registeted baobab123","status":"ok"}

printf '\n'

curl -X POST localhost:1026/account/signup -H "Content-Type: application/json" -d '{"login":"jack", "email":"j123@yandex.ru", "password":"pass", "repeated password":"another_pass"}'
# {"message":"wrong data","status":"error"}

printf '\n'

curl -X POST localhost:1026/account/login -H "Content-Type: application/json" -d '{"login":"jack", "password":"pass"}'
# {"message":"got verification","status":"ok","token":"amFjaw=="}

printf '\n'

curl -X DELETE localhost:1026/account/logout -H "Content-Type: application/json"
# {"message":"no token has been provided"}

printf '\n'

curl -X DELETE localhost:1026/account/logout -H "Content-Type: application/json" -H "Authorization: amFjaw=="

#{"message":"log out: successful for jack","status":"ok"}

printf '\n'

curl -X GET localhost:1026/account/settings -H "Content-Type: application/json" -H "Authorization: amFjaw=="
# {"birthday":"21.03.2002","clusters":"Musicians, Programmers","creation_date":"20.05.2020","first_name":"Antony","gender":"male","last_name":"Bill","login":"baobab123","status":"ok"

printf '\n'

curl -X POST localhost:1026/account/settings -H "Content-Type: application/json" -H "Authorization: amFjaw=="
# {"message":"body is required","status":"error"}

printf '\n'

curl -X POST localhost:1026/account/settings -H "Content-Type: application/json" -H "Authorization: amFjaw==" -d '{"first_name":"new_Jack"}'
# {"message":"successfully defined account settings for jack","status":"ok"

printf '\n'

curl -X POST localhost:1026/account/settings -H "Content-Type: application/json" -d '{"first_name":"new_Jack"}'
# {"message":"no token has been provided"}

printf '\n'

curl -X PATCH localhost:1026/account/settings -H "Content-Type: application/json" -H "Authorization: amFjaw==" -d '{"first_name":"new_Jack"}'
# {"message":"settings fields have been edited","status":"ok"}

printf '\n'

curl -X GET localhost:1026/account/posts -H "Content-Type: application/json" -H "Authorization: aGVsbG8="
# {"posts":["I'm a session guitarist, looking for a band to play together, rehearse. I like to play electric guitar, especially solo! I play mostly hard rock, blues rock.",
# "Hi! I'm looking for a talented songwriter, I'm a good performer, but writing is much worse. Write, I'm waiting for feedback!","We are an aspiring rock band from St. Petersburg, we are looking for a handy technician, namely a sound engineer, it will be great if you are also a sound engineer, write, we are waiting for you!",
# "I'm looking for a trumpeter for joint jams and rehearsals","I love country and blues, I play the guitar and harmonica, a talented keyboard player!"],"status":"ok"}\n
# {"message":"posts have been set successfully","status":"ok"}

printf '\n'

curl -X POST localhost:1026/account/posts -H "Content-Type: application/json" -H "Authorization: aGVsbG8=" -d '{"posts":["value2","value3"]}'
# {"message":"posts have been set successfully","status":"ok"}

printf '\n'

curl -X DELETE localhost:1026/account/posts -H "Content-Type: application/json" -H "Authorization: aGVsbG8=" -d '{"posts":["value2","value3"]}'
# {"message":"posts have been deleted successfully","status":"ok"}

printf '\n'

curl -X GET localhost:1026/account/groups -H "Content-Type: application/json" -H "Authorization: aGVsbG8="

# {"groups":["Progressive-metal fans","ProfessionalDogLovers","SixPistol","BabaJoe","FinalRound"],"status":"ok"}

printf '\n'

curl -X DELETE localhost:1026/account/groups -H "Content-Type: application/json" -H "Authorization: aGVsbG8=" -d '{"posts":["value2","value3"]}'
# {"message":"groups have been deleted successfully","status":"ok"}

printf '\n'

curl -X POST localhost:1026/account/groups -H "Content-Type: application/json" -H "Authorization: aGVsbG8=" -d '{"posts":["value2","value3"]}'
# {"message":"groups have been set successfully","status":"ok"}

printf '\n'

curl -X GET localhost:1026/clusters/
# {"clusters":["Musicians","Artists","Programmers"],"status":"ok"}

printf '\n'

curl -X GET localhost:1026/clusters/?type=
# {"clusters":["Musicians","Artists","Programmers"],"status":"ok"}

printf '\n'

curl -X GET localhost:1026/clusters/?type=artists
# {"clusters":["Artists"],"status":"ok"}

printf '\n'

curl -X GET localhost:1026/clusters/?type=artists+programmers
# {"clusters":["Artists","Programmers"],"status":"ok"}

printf '\n'

curl -X GET localhost:1026/clusters/groups/ -H "Content-Type: application/json"
# {"cluster_groups":[],"status":"ok"}

printf '\n'

curl -X GET localhost:1026/clusters/groups/?type=
# {"cluster_groups":[],"status":"ok"}

printf '\n'

curl -X GET localhost:1026/clusters/groups/?type=musicians
# {"cluster_groups":["NoPainNoGain","MusiciansClusterBastards","HardRockPayesOff"],"status":"ok"}

printf '\n'

