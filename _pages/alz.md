---
title: "Optimized Alzheimer's Disease Diagnostics Machine"
permalink: /alzheimers/
layout: single
classes: wide
excerpt: "An data-efficient Alzheimer's disease predictor"
header:
  overlay_image: /images/IMG_9046.jpg
  caption: "Photo credit: Simon Lee"
date: 2022-09-10

feature_row_left1:
  - url: "https://github.com/Simonlee711/CSE-13S/tree/master/asgn6"
    btn_label: "Code"
    btn_class: "btn--primary"
---

# Abstract

Alzheimer’s disease is a common neurodegenerative brain disorder that slowly begins to deteriorate
our cognitive abilities (thinking, memory, carrying out simple tasks). Alzheimer’s disease has been known
to have an unpredictable disease onset and is therefore hard to detect in its early stages. Therefore, there
is currently a lot of interest in applying deep learning models to learn from MRI images for early diag-
nosis. Using publicly available data from Alzheimer’s Disease Neuroimaging Initiative (ADNI), we train
an optimized Convolutional Neural Network (CNN) model to predict whether a patient has Alzheimer’s
through the features in an image. With a high accuracy, we believe our optimized model can have
an impact in the medical field and assist medical professionals and researchers in advancing pathology-
related tasks. Building these prediction based models can improve diagnostic accuracy, optimize patient
care, and reduce costs by bringing global collaborations.

---

# Keywords

Alzheimer's Disease (AD), Convolutional Neural Networks, Computational Pathology, Deep Learning

---

# Motivation

Alzheimer’s Disease (AD) is a progressive neurodegenerative condition that leads to short-term memory
loss, dementia, and many other cognitive-related issues. These effects are commonly mistaken for the effects
of stress or aging and often go unnoticed. However by the time health professionals do detect Alzheimer’s
it is often too late. For a disease that affects every 1 in 9 (11.3%) people ages 65 and older in the United
States, this has become a rather large scale issue. Traditional practices of diagnosing Alzheimer’s including
a mixture of cognitive tests and brain scans have been difficult markers to track this progression which leaves
health professionals stuck. However in today’s age of data, innovative approaches like machine learning have
helped propel not only the field of pathology but the world. Therefore this research aims to build a image
analysis computational framework that will allow for the early detection of AD.

In order to solve this problem, we need to leverage innovative approaches such as machine learning, which
are computationally intensive and non-traditional in the medical field. However, machine learning techniques
have been increasingly used in disease prediction and visualization to offer prescient and customized pre-
scriptions. In some cases, physicians and medical specialists are left with tough decision making and fear the
extreme penalty of misdiagnosing a patient. So by taking these computational approaches we not only im-
prove the patients’ quality of life, but this also aids physicians in making decisions. With computers showing
promise with its high level of precision, this is only the beginning for this partnership between computation
and healthcare. The goal through this approach is to identify the knowledge gaps, avoid human error and
explore potential opportunities associated with machine learning frameworks.

---

# Deep Learning 

Deep learning is a subsection of machine learning methods, based around neural networks which have the
power to learn based on representation (Schulz et al. 2012). These models learn very similarly to humans
through mimicking the way that neurons signal and communicate from one to the next. Deep learning is
especially important in the field of image analysis because images contain a lot of features (shape, color
histogram, color contrast, texture, etc.). When working with such high dimensional data, a simple machine
learning model will struggle to interpret and return useful data for us to analyze. In contrast, deep learning
models have the ability to process a large number of features which make it very powerful in dealing with
image data. So through the deep learning algorithm called the Convolutional Neural Network, we intend
to be able to accurately predict whether a patient has Alzheimer’s disease from a set of images. In the
preceding sections, we will lay out the foundation, and the underlying background knowledge required to
understand how we obtained our results

---

# Data Availability

Data used in this work were downloaded from the ADNI database run by the Laboratory of NeuroImaging
at the University of Southern California. The ADNI is an ongoing, longitudinal study designed to develop
clinical, imaging, genetic, and biochemical biomarkers for the early detection and tracking of AD through
Magnetic Resonance Imaging (MRI) scans. We therefore use the complete ADNI1 1yr 3T dataset, which
contains 58 AD MRI scans, 113 controlled (CN) MRI scans, and 133 Mild Cognitive Impairment (MCI)
MRI scans for a total of 304 complete 3D brain images. The 3T MRI scan is twice as strong as a standard
1.5T MRI. It operates at a strength of 3T; Tesla (T) is the unit of measurement indicating the strength of
a magnetic field. A stronger magnetic field provides more detailed images, helping doctors and radiologists
see more structures inside the body (Duggan-Jahns et al. 2013). For this reason, we also use this magnetic
strength to get the most clear images for our image analysis.

---

# Model 

{% include figure image_path="images/model.png" alt="this is a placeholder image" caption="CNN Architecture" %}

Now we begin explaining our model that we will use to train for accurate prediction. As seen in the above figure, we can see that a lot is going on before we reach our prediction stage. Therefore in the preceding subsubsections we will break down the processes that goes on within our CNN model.

---

## Preprocessing

Pre-processing is one of the most important steps in machine learning especially in the field of computational biology (Chicco et al. 2017). Data pre-processing is the manipulation and dropping of data to ensure/enhance the performance of the model. Often times if pre-processing is not involved it can lead to misleading results. Especially in medical images, pre-processing is an important step because we often get varying levels of quality, and it is important to run some cleanup on our data before feeding it into our model. 

One of the first major steps during the pre-processing was to convert our MRI scans from the NifTI (.nii) format and into the png lossless image format. We therefore used a python script from the (OfStack et al. 2021) which performs this conversion for us. By performing this important step we greatly reduce our dataset from 11.94 Gb to 52.10 mb which is a 99.60 \% compression rate. We are hoping that through this size reduction, our model can be handle all the data on memory and be trained optimially by not having to feed such a large amount of data during our training process. 

In addition to our file format conversion, we also normalized our image data because some of the MRI scans come at varying qualities. Neural networks process inputs using small weight values, and inputs with large integer values can disrupt or slow down the learning process (Brownlee et al. 2019). As such it is good practice to normalize the pixel values so that each pixel value has a value between 0 and 1. Additionally we also converted the shape of the image to 224 x 224 x 3 which will make it really easy to feed into our Convolutional Neural Network. Our data can be visualized as seen in the below figure.

{% include figure image_path="images/data_vis.png" alt="this is a placeholder image" caption="Our labeled brain data" %}

# Methods

# Results

# Code

{% include feature_row id="feature_row_left1" type="left" %}

# How to run code

