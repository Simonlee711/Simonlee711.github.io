---
title: "Anime Recommendation System"
permalink: /projects/anime/
layout: single
classes: wide
excerpt: "A content-based recommendation system."
header:
 overlay_image: /images/projects/anime.png
 caption: "Anime"
date: 2022-09-11
comments: true
sidebar:
 nav: "docs2"
feature_row_left1:
- url: "https://github.com/Simonlee711/Anime-recommendations"
  btn_label: "Code"
  btn_class: "btn--primary" 
---
 
# Keywords
 
Recommendation Systems, Transformer models, Cosine-similarity functions, anime
 
---
 
# Introducing the concept
 
Artificial Intelligence has widely slipped under the cracks of how apparent it is within our daily lives. One of the fascinating applications of AI has been within the realm of recommendation systems.
 
In a nutshell, a recommender system is a tool that suggests the following content given what you have already seen and liked. Companies like Youtube, Netflix, and Amazon have long used recommender systems to suggest the following video, song, or products you may be widely interested in purchasing. These systems have been very advanced for many years, and by no means will we top them. However, we wanted to try an approach using Natural language processing to showcase similarities between shows and recommend them mathematically using a cosine similarity function.
 
This page and code tutorial showcases our entire pipeline, from data processing down to the algorithms and models. It works pretty incredibly well.
 
---
 
# Dataset
 
{% highlight csv linenos %}
Index,anime_id,name,genre,type,episodes,rating,members,synopsis
3700,1469,Monster Farm: Enbanseki no Himitsu, "Action, Adventure, Comedy, Fantasy",TV,48,6.91,22170, "Genki is a boy who loves playing video games. One day he's zapped into the world of Monster Rancher and meets the girl Holly and the monsters Mochi, Suezo, Golem, Tiger and Hare. Together, they are searching for a way to revive the Phoenix, which is the only monster capable of stopping the evil Moo.(Source: ANN)"
3701,942,Nishi no Yoki Majo: Astraea Testament, "Comedy, Drama, Fantasy, Mystery, Romance",TV,13,6.91,11042, "On Filiels 15th birthday, she received her mothers necklace as a memento from her obstinate astronomer father. Her common and tedious life was turned into a life of conspiracies. With her new life, many adventures await.(Source: ANN)"
3702,29129,Ookami Shoujo to Kuro Ouji Recap,"Comedy, Romance, School, Shoujo",Special,1,6.91,5577,Recap of Ookami Shoujo to Kuro Ouji TV series.
3703,2611,Panda Kopanda, "Comedy, Kids",Movie,2,6.91,4922, "Panda Kopanda (Panda! Go Panda!) is a 30 minute movie made in 1972. Miyazaki created the original idea, the script, the layouts, and did key animation, and Takahata directed the film. The story is about a little girl, Mimiko, who was left alone while her Grandma was away. A 1973 sequel, Panda Kopanda: Amefuri Sakasu no Maki (Panda! Go Panda! & the Rainy-day Circus), continues the story and was made by the same people who made the first movie. The literal translation of the title Panda Kopanda is ""Panda, Baby Panda"", but it's been released in North America as Panda Go Panda.(Source: AniDB)"
3704,1638,Peter Pan no Bouken, "Adventure, Fantasy",TV,41,6.91,2146, "Wendy and her two little brothers are brought to the land of adventures, Neverland, by Peter Pan, a boy who will never grow up. In Neverland they encounter exciting events and meet with little fairies, mermaids, Indians, and pirates. Required to act as a mother, Wendy never has a moment's peace with all that is happening around her, including breath-taking fights with pirates. Later in the series, they set off to find a buried treasure with a map that they obtain from the pirates.(Source: AnimeNfo)"
3705,33420,RESTART POiNTER,Music,Music,1,6.91,364,"Official music video for IDOLiSH7s song ""RESTART POiNTER."""
3706,7245,Sekai Meisaku Douwa: Wow! Maerchen Oukoku,Fantasy,TV,26,6.91,227, "Based on Western tales from the usual suspects: 1001 Nights, C. Perrault, Beaumont, J. & W. Grimm, H. C. Andersen, C. Collodi, English fairytale, H. Pyle, L. Carrol, J. Swift, A. Dumas, E. T. A Hoffman, L. F. Baum, and J. Spyri.Only 21 stories were broadcast, with the last five being released on VHS."
 
{% endhighlight %}
 
We first look at our dataset, which we got from **kaggle**. Kaggle itself scraped the following information and stored them in CSV files from the website [https://myanimelist.net](https://myanimelist.net). At first, our .csv files did not contain any of the synopsis, but because we had the "`anime_id` "feature, we were able to take the "`https://myanimelist.net/ + [anime_id]` "and scrape the code for the summaries. Believe it or not, most of the features in this CSV file were not used. We still have planned future works to continue making an even better recommendation system using all the given features. Let us briefly describe the feature we do use, however.
 
"`synopsis` "- An overview of the anime (i.e., a brief description scraped from https://myanimelist.net)
 
"`name` "- the title of the anime
 
"`genre` "- up to one or more genres that describe the genre of the anime
 
---
 
# BERT NLP Model
 
{% highlight python linenos %}
 
summary_data = df['synopsis']
print("A vector entry of sentences:")
print(summary_data[0])
 
model = SentenceTransformer('distilbert-base-nli-mean-tokens')
embeddings = model.encode(summary_data, show_progress_bar=True)
embed_data = embeddings
 
{% endhighlight %}
 
When working with textual data, the first thing to do is to convert this text into numbers. The reasoning is that computers learn from numbers. Therefore we are converting a string of text (synopsis) into a numeric vector.
 
We take what is called a **transformer model**, specifically the BERT model, to perform this operation. Google has been a big force in the field of Natural language processing and has developed numerous models publicly available at [huggingface](https://huggingface.co/). The company's most recent success has been the DALL-E image generator. Because I was not the one to design the model myself, I would prefer we get some help from Wikipedia to explain what precisely the BERT model does. Wikipedia says the following:
 
*Bidirectional Encoder Representations from Transformers (BERT) is a transformer-based machine learning technique for natural language processing (NLP) pretraining developed by Google. BERT was created and published in 2018 by Jacob Devlin and his colleagues from Google. BERT was pretrained on two tasks: language modeling (15% of tokens were masked, and BERT was trained to predict them from context) and next sentence prediction (BERT was trained to predict if a chosen following sentence was probable or not given the first sentence). As a result of the training process, BERT learns contextual embeddings for words. After pretraining, which is computationally expensive, BERT can be finetuned with fewer resources on smaller datasets to optimize its performance on specific tasks.*
 
{% include figure image_path="images/projects/BERT.png" alt="this is a placeholder image" caption="Berts pre-training and fine tuning visualization" %}
 
Although we now know what BERT is, why is transforming the text into a vector an essential aspect of the pipeline? We say vectors can do all the operations you usually do in machine learning pipelines. In our case, we will use the vectorize test to find the Similarity between two vectors. Our recommendation will be the (5) most similar vectors to the one we are considering.
 
---
 
# Cosine Similarity function
 
{% highlight python linenos %}
 
cos_sim_data = pd.DataFrame(cosine_similarity(X))
def give_recommendations(index,print_recommendation = False):
 \# first variable shows how many recommendations to give
 index_recomm =cos_sim_data.loc[index].sort_values(ascending=False).index.tolist()[1:4]
 anime_recomm =  df['name'].loc[index_recomm].values
 result = {'Anime':anime_recomm,'Index':index_recomm}
 
{% endhighlight %}
 
Let us say x and y are two components. If an anime talks about a high school love story and another one talks more or less about the same stuff, we expect the two vectors to be close. On the other hand, if the other anime is about destroying the world as a titan, we will expect this vector to be far away. To get the proximity between two vectors, we take what is known as the **cosine similarity**, which calculates the cosine of the angle between two vectors. Based on their outputs, we will select the five highest cosine similarity outputs as the recommended anime.
 
{% include figure image_path=" images/projects/cosine-sim.png" alt=" this is a placeholder image" caption=" Cosine Similarity ranks the five highest similar animes based on the anime in the title" %}
 
Moreover, there we have it, an anime recommendation system! This pipeline could be run on many datasets like books, movies, tv shows, etc. All you have to do is make sure you have something that the BERT model can encode into a numerical vector.
 
---
 
# Code
 
This project was done independently with the collaboration of Eugene Lee.
 
"`anime.csv` "- original dataset from kaggle.
 
"`anime_final.csv` "- a dataset that is fed into the pipeline
 
"`anime_pipeline.ipynb` "- a notebook that contains how to run the pipeline
 
"`anime_plus.csv` "- after the synopsis was scraped, they were saved into this CSV.
 
"`parallel.py` "- (irrelevant) a file that tried to parallelize scraping synopsis off myanimelist.com
 
"`project_configs.py` "- a configuration file of constantly used variables
 
"`record.lockfile` "- a record of what files had their files scraped
 
"`requirements.txt` "- all the library requirements needed to run the code
 
"`sql_tutorial.sql` "(irrelevant) - tried to write a query that scrapes other data for future works.
 
"`synopsis_scraper.py` "is the class used to scrape the summary from myanimelist.com.
 
 
{% include feature_row id="feature_row_left1" type="left" %}
 
---
 
# Tutorial on how to run code
 
Step 1. Run the following Jupyter notebook
```
anime_pipeline.ipynb
```
 
---
 
# Collaborator
 
Eugene Lee (eugenelee530@gmail.com)
 
---
 
```
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⡀⠀⠀⠀⢀⣀⣠⣤⣼⣿⣿⣿⣿⣿⣿⣿⣅⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣴⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣯⣽⣢⢤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣯⡍⠲⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠉⠉⢩⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠋⢢⣈⠫⢄⠀⠀⠀⠀⠀⠀⢀⡄⠂⢄⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⣽⣿⣿⣿⣿⣽⣿⣿⣿⣿⣷⡧⠀⠀⠀⠀⢀⠎⠀⠀⠀⢃⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⣿⣿⣿⣿⣿⣿⡟⠀⠀⠀⠀⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣟⣣⠀⠀⠀⡎⠀⠀⠀⠀⠀⡆⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⣿⣿⣿⣿⣿⠏⠀⠀⠀⠀⢠⣿⣿⣿⣿⣿⣿⣿⣿⡋⣿⣿⣿⣿⣿⣿⣿⣿⣿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡔⡄⠀⠁⠀⠀⠀⠀⠀⢰⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⠿⠋⠁⠀⠀⠀⠀⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿⡇⣯⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⡇⢰⠇⠀⠀⠀⠀⠀⡘⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⣼⣼⣿⣿⠿⣿⣿⣿⡿⢹⣿⣿⣿⣿⣿⣿⡽⣯⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠎⠦⡀⠀⠀⠀⢀⠇⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢢⣿⡇⣼⣧⣶⣿⣿⣿⠁⢸⢿⣿⣿⣿⣿⣿⣷⡘⣷⡹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠧⡙⠀⠑⢄⣀⠤⠂⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣟⣼⣿⣿⣿⣿⣿⣿⠀⠀⢛⣿⣿⣿⣿⣿⡿⣿⡬⠿⣾⡻⣿⣿⣿⣿⣿⣿⣿⣿⣿⢯⣿⣿⣿⣿⣿⣻⡆⢰⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠂⠀⣿⢻⣿⣿⣿⣿⣿⣿⣿⡏⠉⠉⠻⢿⣿⣿⣿⣿⣜⢿⣮⡙⠷⣦⣉⠓⢿⣷⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠤⠤⠤⠤⣀⠀⠘⠀⠀⣿⢸⢿⣿⣿⣿⣿⣿⠘⢿⠈⠁⠐⠄⠙⢟⢿⣿⣿⣦⡵⣟⣶⣽⣿⣿⣿⣿⣿⣿⣿⣿⣯⣾⣿⣿⣿⣿⣼⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⢀⠎⠀⠀⠀⠀⠀⠀⠑⠆⠀⠀⣿⠀⣿⣿⣿⣿⣿⣿⣀⣬⣧⣖⣢⠄⠀⠀⠀⠈⠑⠈⠹⠿⠋⠘⣿⣿⣿⡆⣿⣿⣿⡏⡧⣿⣿⣿⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠊⠀⠀⠀⠀⠀⠀⠀⠀⠈⢆⠀⢿⠀⢹⣿⣿⣿⣿⣿⣿⡿⠻⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢮⠴⢃⣿⣿⣿⣿⣷⡟⣿⣿⣿⣿⣿⣟⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠄⠸⡆⡄⢿⣿⣿⣿⣿⣿⡻⢄⠙⢿⣻⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣾⢻⣿⣿⣿⢈⣷⣿⣿⣿⣿⣿⣿⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢱⠐⠹⣵⠀⣿⣿⣿⣿⣿⢿⠦⠀⠀⠀⠀⠀⠀⠂⠀⠀⠀⠀⠀⠀⠀⡠⠞⠁⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡷⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⡁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⠘⢦⣿⣿⣿⣿⣿⣮⣆⠀⠀⠀⠀⠀⠈⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣇⢣⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣦⣤⡤⠀⠀⠀⠀⢀⣀⣀⣀⡀⠀⠀⢀⠴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡌⡆⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⢰⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡅⠀⠀⠀⣾⠇⣿⣿⣿⣿⣿⣿⣿⣿⣶⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⠘⡀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡜⠀⠀⠀⣸⡟⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣢⢄⠀⠀⢀⣤⣶⣿⢟⣿⣿⣿⣿⠰⢸⠾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆⢡⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠰⡀⠀⠀⠀⠀⠀⠀⢀⠜⠀⠀⠀⣰⡟⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⠉⣫⢻⡿⠛⢁⢾⣿⣿⣿⡇⠇⡜⠀⡿⣻⣿⣿⣿⣿⣿⣿⣿⣿⣻⡈⡆⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⢄⠀⠀⠀⡠⠔⠁⠀⠀⠀⣰⡟⠀⠀⣟⣿⣿⣿⣿⣿⣿⠿⠛⠋⠉⠉⠛⠻⢗⠏⠏⢸⢇⢠⠟⣾⣿⣿⣿⣱⠊⠀⠀⡿⡞⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⢸⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠈⠁⠀⠀⠀⠀⢀⡾⠋⠀⠀⣸⠇⣿⣹⣿⣿⣿⣇⠀⠀⠀⠀⠀⠀⠀⡈⠀⠀⠸⢻⠋⢸⣿⣿⣿⢿⠃⠀⠀⠀⣇⠗⢿⡇⢹⣿⣿⢿⣿⣿⣿⣿⣏⡆⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡰⠛⠁⠀⠀⢠⡟⢀⣿⣿⣿⣿⣿⡟⣄⠀⠀⠀⠀⢠⣴⣧⣤⣄⣠⠣⣀⣿⣿⣿⣟⠎⠀⠀⠀⠀⣽⠀⠘⣿⠊⠫⡺⣷⣌⠉⡿⢿⣿⡇⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡠⠊⠀⠀⠀⢀⡠⣾⣁⣼⣿⣿⣿⢹⣿⡇⠈⠑⠂⠀⠀⠈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣽⣿⣿⠇⡜⠘⡄⠀⠹⣧⠀⠈⠪⢙⢻⠷⠦⠿⣿⡄⠀⠀
⠀⠀⢀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡠⠊⠀⣀⠔⣒⣵⣾⣿⣿⣿⣿⣿⣿⡇⢸⣿⠀⠀⡇⠀⠀⠀⠀⣿⣿⣿⣿⠿⣿⣿⣿⣿⣿⣿⣿⣿⢋⡼⠔⠀⠉⢄⡀⠙⣧⠀⣀⡴⠉⠉⠉⠉⠹⣷⡀⠀
⠀⠈⢏⣷⣮⣕⠢⠀⠀⠀⠀⢠⠞⢀⠔⢉⣴⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⠁⣸⠃⠀⠠⠃⠀⠀⠀⢐⡨⠋⠀⣗⡄⢸⣿⣿⡿⡿⣿⡿⢣⠊⠀⠀⠀⠀⠀⠈⠑⠚⠻⣿⣄⣀⡀⠀⢀⣠⣿⣗⡀
⠀⠀⠀⢻⣿⣿⣿⣄⢂⠀⢠⣟⠔⠁⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⢀⠏⣀⠞⠀⠀⠀⠀⠀⠈⠀⠀⠀⣿⠀⢸⣿⣟⠀⢣⠀⡰⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠛⠛⠛⠛⠊⢸⣿⡝
⠀⠀⠀⠀⢻⣿⣿⣿⣆⢃⢸⡏⢀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣾⣿⡁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣧⢸⣿⡟⠀⠸⠊⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⣷
⠀⠀⠀⠀⠀⢻⣿⣿⣿⡞⡔⣣⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣄⠀⠀⠀⠀⠀⠀⠀⠀⣠⠀⠘⠻⡼⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡞⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⢻⣿
⠀⠀⠀⠀⠀⠀⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⠀⠀⠀⠀⠀⠀⢀⠇⠀⠀⠀⠑⠌⠢⠀⣀⣀⠀⠀⠀⠀⠀⠀⣽⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣿⢸⣿
⠀⠀⠀⠀⠀⠀⠈⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣰⣿⣿⣯⣆⠀⠀⠀⠀⠀⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⢸⣿
⠀⠀⠀⠀⠀⠀⠀⠈⣏⠻⢿⣿⣿⣿⣿⣿⣿⡇⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡄⠀⠀⠆⠀⢀⣠⢰⣿⣿⣿⣿⣿⣿⣿⣿⡆⠀⠀⠀⠜⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⡟⢸⡟
⠀⠀⠀⠀⠀⠀⠀⠀⢸⢇⠈⢿⣿⣿⣿⣿⣿⠁⢀⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⡈⣠⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⠀⢠⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⡟⢁⡟⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠘⠀⠆⠈⢿⣿⣿⣿⡇⠀⢸⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⡎⠀⠀⠀⠀⠀⣀⣀⣀⣀⣀⣰⣏⣀⣊⣀⣀
```
 

