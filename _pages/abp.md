---
title: "Arterial Blood Pressure Imputer"
permalink: /abp/
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
  - url: "https://github.com/Simonlee711/CSE-13S/tree/master/asgn6"
    btn_label: "Code"
    btn_class: "btn--primary"
---


# Abstract

Hypotension (a sustained decrease in blood pressure) within critical care patients is associated with a higher risk of mortality and other severe complications. It is periodically monitored non-invasively for all ICU patients. Continuous blood pressure monitoring via arterial line catheters has been shown to lead to faster response times but is also associated with complications such as infection. With recent advances in machine learning, there are current models that are able to predict Arterial Blood Pressure (ABP) continuously and non-invasively but lack perfect precision. Therefore, this project aimed to leverage vasopressors medication from the Electronic Health Records (EHR) to make better-informed predictions. By including the administration rate of vasopressor drugs, we retrained the ABP Imputer deep learning model with the electrocardiogram (EKG) and photoplethysmographic (PPG) waveforms to build a prediction system that takes into account clinical interventions. Our results indicated that the precision of the waveforms is on average 5.67 mmHg away from the actual ABP measurement. These results suggest that our potential new method can measure blood pressure continuously and non-invasively for all patients in the ICU setting and beyond, without the need for any additional instrumentation.

---

# Keywords

Arterial Blood Pressure, V-Net, Imputation, Deep Learning, Data Wrangling, Data Science

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

# Vasopressors

A vasopressor is a drug that healthcare providers use to make blood vessels constrict or become narrow in people with low blood pressure. Often, these are people in shock who are unable to get enough blood to their vital organs. Without oxygen-rich blood, your organs can’t function, which can be fatal. If IV fluids don’t bring your blood pressure up to a normal level, providers can put vasopressors in your IV to help bring your blood pressure up.

Healthcare providers usually give vasopressors through a central venous catheter, or central line, which is an IV tube that goes into a large vein. You may have fewer complications if it’s in your chest or neck instead of your arm.

---

# Methods

---

# Results

---

# Code

{% include feature_row id="feature_row_left1" type="left" %}

---

# How to run code

1. Run the jupyter notebook
```
abp.imputer.ipynb
```

---

# Collaborators

SIMON LEE<sup>1</sup>, Ákos Rudas<sup>2<s/up>, & Jeffrey N. Chiang<sup>2</sup>
1 Bruins in Genomics Summer Program, Institute for Quantitative and Computational Biosciences, UCLA
2 Department of Computational Medicine, University of California, Los Angeles, CA, USA



