---
title: "Arterial Blood Pressure Imputer"
permalink: /projects/abp/
layout: single 
classes: wide
excerpt: "deep learning model that predicts future blood pressure"
header:
  overlay_image: /images/ekg.png
  caption: "ABP Imputation model"
date: 2022-09-10
sidebar:
  nav: "docs2"
feature_row_left1:
  - url: "https://github.com/Simonlee711/ABP_Imputation-EHR"
    btn_label: "Code"
    btn_class: "btn--primary"
---


# Abstract

Hypotension (a sustained decrease in blood pressure) within critical care patients is associated with a higher risk of mortality and other severe complications. It is periodically monitored non-invasively for all ICU patients. Continuous blood pressure monitoring via arterial line catheters has been shown to lead to faster response times but is also associated with complications such as infection. With recent advances in machine learning, there are current models that are able to predict Arterial Blood Pressure (ABP) continuously and non-invasively but lack perfect precision. Therefore, this project aimed to leverage vasopressors medication from the Electronic Health Records (EHR) to make better-informed predictions. By including the administration rate of vasopressor drugs, we retrained the ABP Imputer deep learning model with the electrocardiogram (EKG) and photoplethysmographic (PPG) waveforms to build a prediction system that takes into account clinical interventions. Our results indicated that the precision of the waveforms is on average 5.67 mmHg away from the actual ABP measurement. These results suggest that our potential new method can measure blood pressure continuously and non-invasively for all patients in the ICU setting and beyond, without the need for any additional instrumentation.

---

# Keywords

Arterial Blood Pressure, 1D V-Net, Imputation, Deep Learning, Data Wrangling, Data Science

---

# Motivation

Each year in the United States, 5.7 million patients are admitted to an intensive care unit (ICU) and nearly 50 million patients undergo surgery. Hypotension and hypertension in the ICU and perioperative period are associated with adverse patient outcomes including stroke, myocardial infarction, acute kidney injury, and death. Recent studies even suggest that only a few minutes of hypotension in the acute care setting increases the incidence of these complications. These observations strongly suggest that continuous blood pressure monitoring is critical in the acute care setting to identify periods of hypertension and/or hypotension as early as possible. Today, the gold standard for blood pressure monitoring is the invasive arterial line, a small catheter inserted into an artery, which enables continuous blood pressure monitoring4. However, this technique is highly invasive and is associated with significant complications such as bleeding, hematoma, pseudoaneurysm, infection, nerve damage, and distal limb ischemia, and thus it is only applied to very high-risk patients.

On the other hand, the widely used non-invasive blood pressure monitoring system using cuff-based devices is both inaccurate and intermittent, only allowing for the monitoring of blood pressure every three or five minutes. More recently, devices allowing for continuous and non-invasive blood pressure monitoring have been introduced. These devices, however, are sensitive to patient movement, they are expensive, and they cause continuous pressure on the finger that can interfere with blood circulation. Additionally, the accuracy of the device can deteriorate in patients with severe vasoconstriction, peripheral vascular disease, or distorted fingers due to arthritis10.

The need for measuring the continuous blood pressure non-invasively suggests that the physiological waveform of the blood pressure should be imputed from other data. However, previous attempts at blood pressure imputation have primarily focused on the imputation of discrete systolic and diastolic blood pressure measurements taken intermittently by cuff or at the resolution of a heartbeat while high-risk patients need to be monitored using the continuous arterial line blood pressure waveform, and thus current methods are not adequate for usage in critical care settings. Moreover, many of the previously-studied cohorts consisted of healthy patients at rest, and therefore the blood pressure variability is not as dynamic compared to patients in the ICU. This calls into question the utility of these approaches in real life settings. Finally, many of the existing methods developed and tested their models in the same set of patients by training the model on an earlier part of each patient record and testing the model on the remaining data. Additionally, the number of patients used was often only several dozen, all coming from the same health system. This calls into question the generalizability of the models to unseen patients. For example, Sideris et al. impute the arterial blood pressure waveform by training the model on the same patient for which arterial blood pressure waveforms are provided. However, such a scenario is not clinically useful, since applying such an approach will require invasive monitoring of the patients for at least part of the time.

In this paper, we present the development, training, and validation of a novel non-invasive and continuous deep learning method for predicting the arterial blood pressure waveform using the ECG waveform, the pulse oximeter (PPG) waveform, and non-invasive blood pressure cuff measurements. These measurements are collected as part of the current standard-of-care, and therefore no additional patient monitoring devices are needed. Our method leverages a well-known deep learning model architecture originally designed for image segmentation (V-Net19), and we adapted it for 1D physiological waveform signals. A key aspect of our preprocessing pipeline includes a manual labeling of PPG quality in a large subset of the training data to improve the signal-to-noise ratio and remove artifacts. The manual labeling was used to train a deep neural network to predict the signal quality of the waveform, resulting in a high-quality preprocessing pipeline that can be used beyond the scope of this study. We demonstrate that the modified 1D V-Net approach provides a highly accurate prediction of continuous arterial blood pressure waveform

---

# Data Availability

MIMIC-III is a large, freely-available database comprising deidentified health-related data associated with over forty thousand patients who stayed in critical care units of the Beth Israel Deaconess Medical Center between 2001 and 2012. The database includes information such as demographics, vital sign measurements made at the bedside (~1 data point per hour), laboratory test results, procedures, medications, caregiver notes, imaging reports, and mortality (including post-hospital discharge).

MIMIC supports a diverse range of analytic studies spanning epidemiology, clinical decision-rule improvement, and electronic tool development. It is notable for three factors: it is freely available to researchers worldwide; it encompasses a diverse and very large population of ICU patients; and it contains highly granular data, including vital signs, laboratory results, and medications.

---

# 1D Vnet

We developed a deep learning model that takes as input a window of two signals, ECG and PPG, and several constant values encoded as additional channels by repeating the value for each timestep: the most recent non-invasive systolic, diastolic, and mean blood pressure measurements prior to the window, the time since the most recent NIBP measurement, the median and standard deviation of the pulse arrival time, and heart rate. The model is trained to minimize the residual difference between the PPG scaling method and the true ABP waveform to compensate for the difference in waveform morphology, as well as the change in BP over time. This forces the network to focus on windows where the PPG scaling significantly differs from the ABP waveform, and therefore improve on the PPG scaling method. With enough data and a large enough model, the neural network should be able to similarly learn the scaling method. However, to accelerate the learning process we designed the method to learn the residual error. The model output is a prediction of the residual difference between the continuous ABP waveform and the baseline PPG scaling waveform, and this predicted residual difference is added to the PPG scaling waveform to generate the 1D V-Net waveform prediction. The deep learning model architecture was based on the V-Net CNN architecture, which has been proven to be useful in the field of image segmentation19 (see Supplemental Note 1 for description). However, instead of 2D or 3D image segmentation, we leveraged the V-Net architecture for 1D signal-to-signal transformation. The motivation behind the V-Net architecture is that it learns a compressed representation of the input data to identify global features, and then reconstructs the signal from this representation. During the reconstruction process, local features are learned to modify the waveform at a finer scale. Our architecture is the same as described in the V-Net paper19, except instead of 3D volumes with multiple channels our data is represented as a 1D signal with multiple channels. Otherwise, the architecture (number of layers, convolutions per layer, kernel size, etc.) remained the same. An additional L2 penalty was added to the activation of the final network layer to force the network to prioritize modification of the PPG scaling residual waveform.

To train the network, we used a custom loss function consisting of two parts. The first was the mean squared error between the true ABP waveform and the predicted waveform, which forces the network to learn an accurate prediction of the entire waveform. The second part of the loss was the mean squared error between the true and predicted waveforms at the locations of the systolic and diastolic points, to encourage the network to be particularly accurate at these locations.

The deep-learning model was implemented using Keras32 and was trained for a maximum of 100 epochs using random weight initialization and the Nadam33 optimizer with default parameters beta1 of 0.9, beta2 of 0.999. The learning rate used was 0.001 with a schedule decay of 0.004, and the mini-batch size was 32. For the last layer of the network, an L2 activation penalty with weight 0.0005 was added. Ten percent of the training data was held out for validation, and these data were used for choosing hyperparameters. If the validation loss did not improve after 8 epochs, the model training process was stopped early.

---

# Vasopressors

A vasopressor is a drug that healthcare providers use to make blood vessels constrict or become narrow in people with low blood pressure. Often, these are people in shock who are unable to get enough blood to their vital organs. Without oxygen-rich blood, your organs can’t function, which can be fatal. If IV fluids don’t bring your blood pressure up to a normal level, providers can put vasopressors in your IV to help bring your blood pressure up.

Healthcare providers usually give vasopressors through a central venous catheter, or central line, which is an IV tube that goes into a large vein. You may have fewer complications if it’s in your chest or neck instead of your arm. 

---

# My contribution

My main objective during the 2022 summer was to take the current imputer model and make it slightly better. In the previous section we introduced vasopressors and the big idea is to leverage this drug information to make better preditions. To do this we take advantage of the **Electronic Health Records** (EHR), which is a medical database containing information about a given patient. So not only was I going to be preparing our new data but I was also going to be exploring these EHR systems. 

## Data Wrangling

{% include figure image_path="images/goal.jpg" alt="this is a placeholder image" caption=This is the overview of the data preparation"" %}

The first step was to scrape the EHR for these vasopressor information. The five vasopressors we looked at specifically were:     Epinephrine, Dobutamine, Dopamine, Phenylephrine, Norepinephrine. However part of the challenge was finding out which code associated with which drug. In the healthcare industry most items were masked with a numerical ID for privacy reasons so first step was going through ```D_items.csv``` to extract the 5 numerical ID's. Next we needed to look through ```INPUTEVENTS_MV.csv``` which contained *which patients got what drug*, *the time stamps of administration*, *the end time stamp of administration*, and the *dosage* of the vasopressor. 

{% highlight python linenos %}

df = df.loc[df['ITEM_ID'].isin(drug_ID)]

{% endhighlight %}

Through running this simple one line of code, I was able to filter out all the patients who didn't recieve vasopressor drugs and/or were not administered the 5 drugs named. Once we had the filtered csv file we saved it and proceeded to writing in the drug columns.

## Creating new Drug Columns

Writing in the drug columns turned out to be the biggest pain in the a$$ and ended up taking nearly three out of the eight weeks of my intership. Because each patients ekg, ppg, were being tracked through milliseconds, this resulted into files of upwards to ***100 billion*** rows by 6 columns. The worst part was that we were going to be adding an additional 5 columns for each unique vasopressor which was only going to increase the file size. Right before I was about to generate these new data files, I checked the data size of our dataset and was astonished to see that our dataset came out to **4.4 Terabyte** of data even while compressed. Therefore we needed a clever solution to write out these new drug columns.

One of the most valuable skills I was taught this summer was how to run code in parallel. And since the ```halperingpu``` had up to 80 gpu cores, I was allowed to use up to 20 of them. In addition I became inspired by the TV show "Silicon Valley" where they make an optimized compression algorithm called mid-out. Similarly I was going to start at the first and last patients data files and meet in the middle. A visual is displayed below:

{% include figure image_path="images/parallel.jpg" alt="this is a placeholder image" caption="A procedure" %}

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

## retrain model

Last part of my summer was to simply retrain the imputer model with this new data that I had generated. Everything was essentially written within ```abp_imputer.ipynb``` and all I had to do was change the ```git_configs.py``` and ```abp_model.py``` files so that it took in the correct amount of features. However due to time constraints, I was unable to test on the 4000+ patient files I generated in the summer. We couldn't find a way to load the data and training would have taken an extremely long time if I had trained on the whole patient sample. Therefore Dr. Akos Rudas and Dr. Jeffrey Chiang are currently working on working on those two aspects that I could not. Our hope is to release a published paper after its completion.

---

# Results

In this section we take a look at the results generated by the imputer pipeline.

---

## Regression based Predicitions

Our first set of plots show three different 4 second frames which contain the true waveform, the predicted waveform without the medication, and the predicted waveform with the medication. Though these are just random samples, we can see that both models tend to show off pretty quality level results.

{% include figure image_path="images/p1.png" alt="this is a placeholder image" caption="" %}

{% include figure image_path="images/p2.png" alt="this is a placeholder image" caption="" %}

{% include figure image_path="images/p3.png" alt="this is a placeholder image" caption="Predictions for all three waveforms" %}

We see differentiation between the first model versus our current model which takes into account clinical interventions. In each particular frame, it is a rather close race in determining which prediction is actually doing better. Therefore we need a better suited test to identify our results.

---

## Bland–Altman

To evaluate the agreement between the gold standard invasive blood pressure measurements (the arterial catheter) and the DNN predictions, we used the Bland and Altman method as this is the standard method for comparing the agreement of two medical devices. Accuracy and precision of the predictions were described as the mean ± standard deviation of the differences between the predicted and true blood pressure values, and the differences are considered acceptable by the Association for the Advancement of Medical Instrumentation (AAMI) criteria if less than 5 ± 8 mmHg. The method was implemented as follows. For each window under consideration, we extracted the systolic and diastolic blood pressure measurements from the ABP waveform using the peak finding algorithm described previously. These measurements were used as the gold standard reference values. We then used the peak finding algorithm on the DNN-generated waveform to determine the systolic and diastolic blood pressure measurements and used these as the comparison values. If the number of systolic or diastolic points identified by the peak finding algorithm differed between the true and predicted waveforms, we performed local alignment by minimizing the sum of the differences between the indices of the true and predicted waveform points. We then took the difference between the reference blood pressure measurement and the predicted blood pressure measurement pairs, and plotted these differences as a function of the average of the reference and predicted value pairs. Our results show as follows:

{% include figure image_path="images/ba1.png" alt="this is a placeholder image" caption="Bland Altman with Medication data" %}

{% include figure image_path="images/ba2.png" alt="this is a placeholder image" caption="Bland Altman without Medication data" %}

---

# Code
This project was done in part of the Bruin in Genomics Summer 2022 Internship at UCLA. I worked under Dr. Jeffrey Chiang, and was supervised by Dr. Akos Rudas. Below I will list the source files that were made in this assignment as well as the code linked below it.

```figures``` - a folder where all the data generated is saved

```models``` - some needed .py files in order to run the ```abp_imputer.ipynb``` pipeline

```src``` - contains some preprocessing and model .py files

```vnet_32s_mimic``` - where the pipeline variables are stored for reproducability

```vnet_32s_mimic_simon``` - where the pipeline variables are stored for reproducability (personal folder)

```waveFormProject``` - some files I made during my internship

```abp_imputer.ipynb``` - the jupyter notebook containing the pipeline

```project_configs_simon.py``` - a configurations file that contains widely reused variables and folder paths

{% include feature_row id="feature_row_left1" type="left" %}

---

# How to run code

1. Run the jupyter notebook
```
abp_imputer.ipynb
```

---

# Collaborators

SIMON LEE<sup>1</sup>, Ákos Rudas<sup>2</sup>, & Jeffrey N. Chiang<sup>2</sup>
1 Bruins in Genomics Summer Program, Institute for Quantitative and Computational Biosciences, UCLA
2 Department of Computational Medicine, University of California, Los Angeles, CA, USA



