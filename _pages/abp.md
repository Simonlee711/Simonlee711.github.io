---
title: "Arterial Blood Pressure Imputer"
permalink: /projects/abp/
layout: single
classes: wide
excerpt: "Deep learning model that predicts future blood pressure"
header:
 overlay_image: /images/projects/ekg.png
 caption: "ABP Imputation model"
date: 2022-10-01
sidebar:
 nav: "docs2"
feature_row:
 - url: "https://github.com/Simonlee711/ABP_Imputation-EHR"
   btn_label: "Code"
   btn_class: "btn--primary"
 - url: "https://Simonlee711.github.io/files/Poster.pdf"
   btn_label: "Poster"
   btn_class: "btn--primary"
 - url: "https://Simonlee711.github.io/files/BIG%20Summer%20Project.pdf"
   btn_label: "Slides"
   btn_class: "btn--primary"
---
 
 
# Abstract
 
Hypotension (a sustained decrease in blood pressure) within critical care patients is associated with a higher risk of mortality and other severe complications. It is periodically monitored non-invasively for all ICU patients. Continuous blood pressure monitoring via arterial line catheters has been shown to lead to faster response times but is also associated with complications such as infection. With recent advances in machine learning, there are current models that are able to predict Arterial Blood Pressure (ABP) continuously and non-invasively but lack perfect precision. Therefore, this project aimed to leverage vasopressors medication from the Electronic Health Records (EHR) to make better-informed predictions. By including the administration rate of vasopressor drugs, we retrained the ABP Imputer deep learning model with the electrocardiogram (EKG) and photoplethysmographic (PPG) waveforms to build a prediction system that takes into account clinical interventions. Our results indicated that the precision of the waveforms is on average 5.67 mmHg away from the actual ABP measurement. These results suggest that our potential new method can measure blood pressure continuously and non-invasively for all patients in the ICU setting and beyond, without the need for any additional instrumentation.
 
---
 
# Keywords
 
Arterial Blood Pressure, 1D V-Net, Imputation, Deep Learning, Data Wrangling, Data Science
 
---
 
# Motivation
 
Every year in the USA, millions of patients are admitted into the intensive care unit (ICU) and millions of patients undergo surgery. Hypotension and hypertension in the ICU are two common and scary outcomes that can lead to future complications like stroke, myocardial infarction, acute kidney injury, and even death. Recent studies have shown that only a few minutes of time separate hypotension from causing serious complications. These observations have strongly suggested that we need a new methodology that is able to predict continuously and non-invasively in case of hypotension or hypertension. The current methodology for blood pressure monitoring is a catheter that is inserted into an artery which enables continuous measurements of blood pressure. However this technique is invasive and has led to future complications such as bleeding, hematoma, pseudoaneurysm, etc., and is therefore only applied to very high-risk patients.
 
On the other hand, there is a non-invasive blood pressure monitoring system using a cuff based device which is non-continuous and often inaccurate allowing for measurements roughly every three to five minutes. While new medical devices have been recently engineered, there are still issues like sensitivity to patient movement, price, and interference of blood circulation that have made them not the gold standard.
 
Therefore there is a massive need for a continuous and non-invasive blood pressure monitoring system. We therefore present the development, training, and validation of a novel deep learning methodology for predicting arterial blood pressure (ABP) using the Electrocardiogram (EKG) waveform, the pulse oximeter (PPG) waveform, and non-invasive pressure cuff measurements. These measurements are collected as part of the current standard-of-care, and have therefore not needed any additional monitoring devices. The method leverages a well known deep learning architecture that is utilized frequently in image segmentation, and is adapted to the one-dimensional physiological waveform signals. In addition to building off the original model, we are going to be including 5 additional clinical intervention channels to our one dimensional waveforms. These channels are going to be specifically targeted vasopressor information that were administered when patients were experiencing low blood pressure. Our hope for integrating clinical interventions is to provide more sharp predictions from our model. We demonstrate that the new 1D V-Net approach with clinical interventions provides a highly accurate prediction of continuous arterial blood pressure waveform compared to its original model.
 
---
 
# Data Availability
 
MIMIC-III is a large, freely-available database comprising de-identified health-related data associated with over forty thousand patients who stayed in critical care units of the Beth Israel Deaconess Medical Center between 2001 and 2012. The database includes information such as demographics, vital sign measurements made at the bedside (~1 data point per hour), laboratory test results, procedures, medications, caregiver notes, imaging reports, and mortality (including post-hospital discharge).
 
MIMIC supports a diverse range of analytic studies spanning epidemiology, clinical decision-rule improvement, and electronic tool development. It is notable for three factors: it is freely available to researchers worldwide; it encompasses a diverse and very large population of ICU patients; and it contains highly granular data, including vital signs, laboratory results, and medications.
 
---
 
# 1D Vnet
 
In the first model, a deep learning model was developed that takes in two primary inputs: ECG and PPG, and some additional encoded channels of repeating values of non-continuous measurements (the most recent non-invasive systolic, diastolic, and mean blood pressure measurements prior to the window, the time since the most recent NIBP measurement, the median and standard deviation of the pulse arrival time, and heart rate). The model is trained to reduce the residual difference between the original model without the clinical interventions vs. the new one with the clinical interventions. In the original paper they said that the "network is to focus on windows where the PPG scaling significantly differs from the ABP waveform, and therefore improve on the PPG scaling method". Like many neural networks, with adequate amounts of data, the neural network should be able to produce a prediction that is similar to the true value. Within the pipeline, there are processes to increase the training time by designing a method that is able to learn the residual error. The model output is a prediction of the residual difference between the continuous ABP waveform and the baseline PPG scaling waveform, and this predicted residual difference is added to the PPG scaling waveform to generate the 1D V-Net waveform prediction.
 
The deep learning model was based on a fancy CNN known as the V-Net, which has been used primarily in image segmentation. However the original model was not looking in a two-dimensional or three dimensional space and was cleverly designed to take a 1 dimensional signal-to-signal transformation with multiple channels (PPG, EKG, etc.). This was a result of feature engineering done by the original model. The model selection was determined by its ability to learn a compressed representation of the input data to identify global features, and then reconstructs the signal from this representation. What this means for our model is that we simply need to change a tiny parameter in the Keras 1D V-Net model which now takes in additional N+ channels that will be used as additional channels to train the model.
 
---
 
# Vasopressors
 
A vasopressor is a drug that healthcare providers use to make blood vessels constrict or become narrow in people with low blood pressure. Often, these are people in shock who are unable to get enough blood to their vital organs. Without oxygen-rich blood, your organs can’t function, which can be fatal. If IV fluids don’t bring your blood pressure up to a normal level, providers can put vasopressors in your IV to help bring your blood pressure up.
 
Healthcare providers usually give vasopressors through a central venous catheter, or central line, which is an IV tube that goes into a large vein. You may have fewer complications if it’s in your chest or neck instead of your arm.
 
---
 
# My contribution
 
My main objective during the 2022 summer was to take the current imputer model and make it slightly better. In the previous section we introduced vasopressors and the big idea is to leverage this drug information to make better predictions. To do this we take advantage of the **Electronic Health Records** (EHR), which is a medical database containing information about a given patient. So not only was I going to be preparing our new data but I was also going to be exploring these EHR systems.
 
## Data Wrangling
 
{% include figure image_path="images/projects/goal.jpg" alt="this is a placeholder image" caption="This is the overview of the data preparation" %}
 
The first step was to scrape the EHR for this vasopressor information. The five vasopressors we looked at specifically were:     Epinephrine, Dobutamine, Dopamine, Phenylephrine, Norepinephrine. However part of the challenge was finding out which code associated with which drug. In the healthcare industry most items were masked with a numerical ID for privacy reasons so the first step was going through ```D_items.csv``` to extract the 5 numerical ID's. Next we needed to look through ```INPUTEVENTS_MV.csv``` which contained *which patients got what drug*, *the timestamps of administration*, *the end timestamp of administration*, and the *dosage* of the vasopressor.
 
{% highlight python linenos %}
 
df = df.loc[df['ITEM_ID'].isin(drug_ID)]
 
{% endhighlight %}
 
Through running this simple one line of code, I was able to filter out all the patients who didn't receive vasopressor drugs and/or were not administered the 5 drugs named. Once we had the filtered csv file we saved it and proceeded to write in the drug columns.
 
## Creating new Drug Columns
 
Writing in the drug columns turned out to be the biggest pain in the a$$ and ended up taking nearly three out of the eight weeks of my internship. Because each patient's ekg, ppg, were being tracked through milliseconds, this resulted into files of upwards to ***100 billion*** rows by 6 columns. The worst part was that we were going to be adding an additional 5 columns for each unique vasopressor which was only going to increase the file size. Right before I was about to generate these new data files, I checked the data size of our dataset and was astonished to see that our dataset came out to **4.4 Terabyte** of data even while compressed. Therefore we needed a clever solution to write out these new drug columns.
 
One of the most valuable skills I was taught this summer was how to run code in parallel. And since the ```halperingpu``` had up to 80 gpu cores, I was allowed to use up to 20 of them. In addition I became inspired by the TV show "Silicon Valley" where they make an optimized compression algorithm called mid-out. Similarly I was going to start at the first and last patients' data files and meet in the middle. A visual is displayed below:
 
{% include figure image_path="images/projects/parallel.jpg" alt="this is a placeholder image" caption="A procedure inspired by *Silicon Valley* to make drug columns" %}
 
The large idea was that if I could write out the drug columns and save that entry within a ```lockfile.lock``` then we could keep the progress of which files have been written into and which have not. Therefore using this Silicon valley inspired parallelized function I ran it.  and it still took nearly two weeks until it was finished... The code is shown below:
 
{% highlight python linenos %}
 
def time_calculator(start, end, drug_amt):
   '''
   calculates the end and start time of the patients drug administration
   and calculates the rate in which the drug is administered
   '''
   d1 = datetime.strptime(end, "%Y-%m-%d %H:%M:%S")
   d2 = datetime.strptime(start, "%Y-%m-%d %H:%M:%S")
 
   difference = d1.timestamp() - d2.timestamp()
   rate = drug_amt/float(difference * 1000)
 
   return rate
 
def write_files(file):
  
   df = pd.read_csv('/data2/mimic/ABP_with_Med_data/mg/mg_INPUTEVENTS_MV.csv.gz', compression='gzip')
   fileID = file[:18]
   print(fileID)
 
   l = []
   for i in os.listdir('/data2/mimic/ABP_with_Med_data/patients/flags'):
       i = i[:18]
       l.append(i)
  
   if fileID not in l:
       print("skipped")
       return 0
  
   df = df.loc[df['date+ID'].isin([fileID])]
   #display(df)
   print("found something")
   df = df.reset_index()
   df_out = pd.read_csv('/data2/mimic/ABP_with_Med_data/patients/' + file ,compression='gzip')
   print("read in wave file")
   try:
       for i in range(len(df)):
           s = df['STARTTIME'].at[i]
           st = df['ENDTIME'].at[i]
           amount = df['AMOUNT'].at[i]
           rate = time_calculator(s, st, amount)
           print(rate)
           value = s+'.000'
           value2 = st+'.000'
           beg = (df_out[df_out['Unnamed: 0.1'] == value].index.values)
           end = (df_out[df_out['Unnamed: 0.1'] == value2].index.values)
           if rate == 0:
               continue
           # insert drug info to right column
           if df['ITEMID'][i] == 221906:
               df_out['Norepinephrine'][beg[0]:end[0]] = rate
           elif df['ITEMID'][i] == 221749:
               df_out['Phenylephrine'][beg[0]:end[0]] = rate
           elif df['ITEMID'][i] == 221662:
               df_out['Dopamine'][beg[0]:end[0]] = rate
           elif df['ITEMID'][i] == 221653:
               df_out['Dobutamine'][beg[0]:end[0]] = rate
           elif df['ITEMID'][i] == 221289:
               df_out['Epinephrine'][beg[0]:end[0]] = rate
           else:
               continue
           print("columns have successfully been put in")
           if len(df) >= 2 and i % 2 ==0:
               df_out.to_csv('/data2/mimic/ABP_with_Med_data/patients/' + file ,compression='gzip')
               print("file successfully wrote out") 
       os.remove('/data2/mimic/ABP_with_Med_data/patients/flags/' + fileID + '.txt')
       return 1
   except IndexError:
       print("something failed")
       os.remove('/data2/mimic/ABP_with_Med_data/patients/flags/' + fileID + '.txt')
       return 0
      
 
if __name__ == "__main__":
   l = []
   for i in os.listdir('/data2/mimic/ABP_with_Med_data/patients'):
       l.append(i)
   os.chdir('/data2/mimic/ABP_with_Med_data/patients')
 
   with Pool(6) as executor:
       results = executor.map(write_files, l)
 
{% endhighlight %}
 
## Retrain model
 
Last part of my summer was to simply retrain the imputer model with this new data that I had generated. Everything was essentially written within ```abp_imputer.ipynb``` and all I had to do was change the ```git_configs.py``` and ```abp_model.py``` files so that it took in the correct amount of additional channels within our one dimensional waveform. However due to time constraints, I was unable to test on the 4000+ patient files I generated in the summer. We couldn't find a way to load the data and training would have taken an extremely long time if I had trained on the whole patient sample. Therefore Dr. Akos Rudas and Dr. Jeffrey Chiang are currently working on those two aspects that I could not. Our hope is to release a published paper after its completion.
 
---
 
# Results
 
In this section we take a look at the results generated by the imputer pipeline.
 
---
 
## Regression based Predictions
 
Our first set of plots show three different 4 second frames which contain the true waveform, the predicted waveform without the medication, and the predicted waveform with the medication. Though these are just random samples, we can see that both models tend to show off pretty quality level results.
 
{% include figure image_path="images/projects/p1.png" alt="this is a placeholder image" caption="" %}
 
{% include figure image_path="images/projects/p2.png" alt="this is a placeholder image" caption="" %}
 
{% include figure image_path="images/projects/p3.png" alt="this is a placeholder image" caption="Predictions for all three waveforms" %}
 
We see differentiation between the first model versus our current model which takes into account clinical interventions. In each particular frame, it is a rather close race in determining which prediction is actually doing better. Therefore we need a better suited test to identify our results.
 
---
 
## Bland–Altman
 
In order to verify that this model is within the gold standard of invasive blood pressure measurements, we use a method known as the Bland Altman. This Bland ALtman method is the standard method for comparing the agreement between two medical devices. Accuracy and precision of the predictions were described as the mean ± standard deviation of the differences between the predicted and true blood pressure values, and the differences are considered acceptable by the Association for the Advancement of Medical Instrumentation (AAMI) criteria if less than 5 ± 8 mmHg. For each four second window under consideration, we use the peak finding algorithm within our ```ABP_imputer.ipynb``` pipeline to find the systolic and diastolic blood pressure measurements of our ABP waveform. These measurements can then be used as the standard reference values that we can compare within our model. We then use the peak finding algorithm on our predicted waveforms to similarly get a set of predicted systolic and diastolic points and compare these to our reference waveforms. By taking the local alignment by minimizing the sum of differences between indices, we were able to see the difference between the true and predicted. The goal of these plots is to obviously have a wide distribution of our data be centered around the zero line meaning it is widely accurate across a wide range of blood pressure measurements.
 
{% include figure image_path="images/projects/ba1.png" alt="this is a placeholder image" caption="Bland Altman with Medication data" %}
 
{% include figure image_path="images/projects/ba2.png" alt="this is a placeholder image" caption="Bland Altman without Medication data" %}
 
Based on our data we can see that our model does tend to be performing better, but also contains bias. This bias from my understanding is that we only took into account specific clinical interventions (vasopressors) which would only improve the predictions based on the lower blood pressure. Therefore we can see at higher blood pressures, the variability is much greater causing a diagonal distribution. Meanwhile we can see that the original model had no such relationship and was just widely variable. It is safe to say that the predictions done on this small subset of data are only small implications, and I look forward to seeing the results of the 4000+ patient model that is currently in the works.
 
---
 
# Code
 
The code is not publicly available for privacy reasons between the Collaborators and I. Our future hope is that we do publish the code along with the new paper.
 
<!---
# Code
This project was done in part of the Bruin in Genomics Summer 2022 Internship at UCLA. I worked under Dr. Jeffrey Chiang, and was supervised by Dr. Akos Rudas. Below I will list the source files that were made in this assignment as well as the code linked below it.
 
```figures``` - a folder where all the data generated is saved
 
```models``` - some needed .py files in order to run the ```abp_imputer.ipynb``` pipeline
 
```src``` - contains some preprocessing and model .py files
 
```vnet_32s_mimic``` - where the pipeline variables are stored for reproducibility
 
```vnet_32s_mimic_simon``` - where the pipeline variables are stored for reproducibility (personal folder)
 
```waveFormProject``` - some files I made during my internship
 
```abp_imputer.ipynb``` - the jupyter notebook containing the pipeline
 
```project_configs_simon.py``` - a configurations file that contains widely reused variables and folder paths
 
{% include feature_row %}
 
---
 
# How to run code
 
1. Run the jupyter notebook
```
abp_imputer.ipynb
```
-->
---
 
# Collaborators
 
SIMON LEE<sup>1</sup>, Ákos Rudas<sup>2</sup>, & Jeffrey N. Chiang<sup>2</sup>
1 Bruins in Genomics Summer Program, Institute for Quantitative and Computational Biosciences, UCLA
2 Department of Computational Medicine, University of California, Los Angeles, CA, USA
 
 
 
 
 

