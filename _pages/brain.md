---
title: "Processing Faces - Brain Activity Modeling"
permalink: /projects/brain/
layout: single
classes: wide
excerpt: "Modeling visual brain activity"
header:
 overlay_image: /images/projects/brain1/brain_cover.png
 caption: "Photo credit: Simon Lee"
date: 2022-10-15
sidebar:
  nav: "docs2"
feature_row_left1:
- url: "https://github.com/Simonlee711/EPFL/blob/main/NX-422-Neural-Signals-Procesing/MiniProject_1/mini_project_1.ipynb"
  btn_label: "Code"
  btn_class: "btn--primary" 
---

{% include figure image_path="images/construction.jpg" alt="this is a placeholder image" caption="Web Page is currently under development" %}

# Motivation

Imagine that we are interested in identifying which region of the brain is involved in processing faces. We can explore this question by showing participants different types of faces where each face represents one trial. If we scanned someone with this design, we could expect to see any region involved in processing faces increase in activation around the time of the face presentation. To understand which of these regions process faces we would need to add at least one other condition/visual stimulus that will serve as a visual control. It’s usually a visual stimulus that has similar properties to a face in terms of luminance and colour. In this mini-project, we’ll see how the general linear model (GLM) can be used to make inferences about brain responses in a single subject. Given the simulated time series for a single voxel that resembles real data, we can evaluate how well we can recover the true signal using a general linear model.

---

# Keywords

General Linear Model (GLM), convolution, signals processing, brain activation 

---

# Introduction

Understanding brain functions and their localisation within the nervous system has been a fascination to scientists for a long time and has split opinions throughout history; from René Descartes’ dualistic view of a separate body and mind, Gall’s phrenology, all the way to Pierre Flourens’ holistic view. 

These turbulent debates were only dissipated thanks to the apparition of magnetic resonance imaging (MRI) used to non-invasively obtain structural images of the brain as well as functional MRI (fMRI). As neuronal activity triggers increased blood flow in the respective area, detecting the deoxygenated haemoglobin molecules (paramagnetic) gives insight in brain action. The resulting “Blood Oxygenation Level Dependent” (BOLD) signal depends on blood oxygenation, blood volume and blood flow. Unfortunately, the raw information collected with fMRI is often not easily interpretable as a result of noise and other brain activity. However, the desired brain activity can be visualised by creating a model linking the input stimulus to the output fMRI data. By fitting the model to the raw data and by plotting its weights onto a structural MRI image, it becomes apparent which voxels react strongly to the stimulus, effectively identifying the brain region responsible for a specific process. These technical advancements resulted in the general adoption of the distributed processing view of the brain, in which different areas are responsible for specific tasks and complex processes are a result of the interactions between them. 

The complex function of interest in this project is the identification of faces. The core system responsible for facial recognition consists of three regions of the occipitotemporal visual extrastriate cortex. The first region is the inferior occipital gyrus and is associated with the perception of the structural facial features. The second is superior temporal sulcus and is related to changeable aspects of faces, such as perception of eye gaze and facial expressions. Finally the third region is the lateral fusiform gyrus and participates in identity recognition. In addition, the extended system includes brain regions that do not solely participate in facial recognition, but aid the core system by extracting other meaningful information. One example is the amygdala, which, together with the insula, processes the emotional content of faces.

In this project, we will try to understand how we can use a general linear model (GLM) to extract information from brain signals. For simplification purposes, we will treat the data from a single voxel. 

---

# Methods

In order to acquire a detailed understanding of fMRI and of the modelling of the resulting data, we will first build a fake raw fMRI signal and then decode it with a mathematical model.
We mimic showing participants images of faces by creating an input signal consisting of a series of rectangular pulses of 2 seconds in duration each. The convolution of this input signal with the ideal Haemodynamic Response Function (HRF), which is the response to an ideal impulse stimulus (Dirac delta), gives us the ideal output data. A representation of this output is achieved by adding normally distributed noise to the ideal data.

{% include figure image_path="images/projects/brain1/stimulus.png" alt="this is a placeholder image" caption="Our Brain Voxel Stimuli" %}

A mathematical model is then fitted to the obtained imitation of raw fMRI data. The model is linear and of first order, with weight optimisation achieved by least squares with a mean square error cost function. The resulting optimal weights will be tested for statistical significance from the null hypothesis by

{% include figure image_path="images/projects/brain1/convolution.png" alt="this is a placeholder image" caption="Visual Demonstration of Convolution" %}

**page is not finished**

---

# Results

**page is not finished**

{% include figure image_path="images/projects/brain1/prediction.png" alt="this is a placeholder image" caption="After fitting the GLM we can recover our convoluted Signal with accurate precision for a linear model" %}

---

# Discussion

---

# Future Direction

fMRI is composed of many voxels and to get a holistic view of this model, a future direction is to be able to compute all the regressors for all the voxels of the brain manually. After doing so we can see the regressors at every voxel to see where the heightened regressors or stimulus activation occurs. Though there are currently advanced libraries that are able to visualize this for us (shown at the end of the jupyter notebook), manually running this process could allow us to gain insight into the inner workings of these advanced libraries.

---

# Code
This project was done in NX-421 (Neural Signals & Signals Processing) at EPFL taught by Professor Dimitri Van De Ville as my mini project. Below I will list the source files that were made in this assignment as well as the code linked below it.

```mini_project_1.ipynb``` - the notebook that executes the stimulus recognition pipeline

```example_voxel_signal.npy``` - the numpy file containing an example voxel

{% include feature_row id="feature_row_left1" type="left" %}

---

# References

Principles of Neural Science, Sixth Edition, 2021 - McGraw Hill. By Eric R. Kandel, John D. Koester, Sarah H. Mack and Steven A. Siegelbaum.

Human Neural Systems for Face Recognition and Social Communication
James V. Haxby, Elizabeth A. Hoffman, and M. Ida Gobbini

---

# Collaborators

- Simon Lee 
- Julian Thomas Bär
- Veronika Calati
- Merkourios Simos
