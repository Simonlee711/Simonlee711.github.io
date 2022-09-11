---
title: "Anime Recommendation System"
permalink: /anime/
layout: splash 
classes: wide
excerpt: "A content based recommendation system"
header:
  overlay_image: /images/anime.png
  caption: "Photo credit: Simon Lee"
date: 2022-09-10
---
# Collaborator

Eugene Lee (eugenelee530@gmail.com)

# Keywords: 

Recommendation Systems, Transformer models, Cosine-similarity functions, anime

# Introducing the concept

Artificial Intellegence has widely slipped under the cracks of how appparent it is within our daily lives. One of the most fascinating applications of AI has been within the realm of recommendation systems.

In a nutshell, a recommender system is a tool that suggests you the next content given what you have already seen and liked. Companies like Youtube, Netflix and Amazon have long used recommender systems to suggest you the next video or song to suggest products that you may be widely interested in purchasing. These systems have been very advanced for many years and by no means are we going to top them. However we wanted to try an approach using Natural language processing to showcase similarities between shows and recommend them mathematically using a cosine similarity function.

This page and code tutorial showcases our entire pipeline from data processing all the way down to the algorithms and models and it actually works quite incredibly well. 

# Dataset

{% highlight csv linenos %}
,Unnamed: 0.1,Unnamed: 0,anime_id,name,genre,type,episodes,rating,members,synopsis
0,0,3700,1469,Monster Farm: Enbanseki no Himitsu,"Action, Adventure, Comedy, Fantasy",TV,48,6.91,22170,"Genki is a boy who loves playing video games. One day hes zapped into the world of Monster Rancher and meets the girl Holly and the monsters Mochi, Suezo, Golem, Tiger and Hare. Together, they are searching for a way to revive the Phoenix, which is the only monster capable of stopping the evil Moo.(Source: ANN)"
1,1,3701,942,Nishi no Yoki Majo: Astraea Testament,"Comedy, Drama, Fantasy, Mystery, Romance",TV,13,6.91,11042,"On Filiels 15th birthday, she received her mothers necklace as a memento from her obstinate astronomer father. Her common and tedious life was turned into a life of conspiracies. With her new life, many adventures await.(Source: ANN)"
2,2,3702,29129,Ookami Shoujo to Kuro Ouji Recap,"Comedy, Romance, School, Shoujo",Special,1,6.91,5577,Recap of Ookami Shoujo to Kuro Ouji TV series.
3,3,3703,2611,Panda Kopanda,"Comedy, Kids",Movie,2,6.91,4922,"Panda Kopanda (Panda! Go Panda!) is a 30 minute movie made in 1972. Miyazaki created the original idea, the script, the layouts, and did key animation, and Takahata directed the film. The story is about a little girl, Mimiko, who was left alone while her Grandma was away. A 1973 sequel, Panda Kopanda: Amefuri Saakasu no Maki (Panda! Go Panda! & the Rainy-day Circus), continues the story and was made by the same people who made the first movie. The literal translation of the title Panda Kopanda is ""Panda, Baby Panda"", but it`s been released in North America as Panda Go Panda.(Source: AniDB)"
4,4,3704,1638,Peter Pan no Bouken,"Adventure, Fantasy",TV,41,6.91,2146,"Wendy and her two little brothers are brought to the land of adventures, Neverland, by Peter pan, a boy who will never grow up. In Neverland they encounter exciting events and meet with little fairies, mermaids, Indians, and pirates. Required to act as a mother, Wendy never has a moments peace with all that is happening around her, including breath-taking fights with pirates. Later in the series, they set off to find a buried treasure with a map that they obtain from the pirates.(Source: AnimeNfo)"
5,5,3705,33420,RESTART POiNTER,Music,Music,1,6.91,364,"Official music video for IDOLiSH7s song ""RESTART POiNTER."""
6,6,3706,7245,Sekai Meisaku Douwa: Wow! Maerchen Oukoku,Fantasy,TV,26,6.91,227,"Based on Western tales from the usual suspects: 1001 Nights, C. Perrault, Beaumont, J. & W. Grimm, H. C. Andersen, C. Collodi, English fairytale, H. Pyle, L. Carrol, J. Swift, A. Dumas, E. T. A Hoffman, L. F. Baum, and J. Spyri.Only 21 stories were broadcast, with the last five being released on VHS."

{% endhighlight %}