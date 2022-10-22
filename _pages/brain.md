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

# Motivation

Imagine that we are interested in identifying which region of the brain is involved in processing faces. We can explore this question by showing participants different types of faces where each face represents one trial. If we scanned someone with this design, we could expect to see any region involved in processing faces increase in activation around the time of the face presentation. To understand which of these regions process faces we would need to add at least one other condition/visual stimulus that will serve as a visual control. It’s usually a visual stimulus that has similar properties to a face in terms of luminance and colour. In this mini-project, we’ll see how the general linear model (GLM) can be used to make inferences about brain responses in a single subject. Given the simulated time series for a single voxel that resembles real data, we can evaluate how well we can recover the true signal using a general linear model.

---

# Keywords

General Linear Model (GLM), convolution, signals processing, brain activation 

---

# Introduction

Understanding brain functions and their localisation within the nervous system has been a fascination to scientists for a long time and has split opinions throughout history; from René Descartes’ dualistic view of a separate body and mind, Gall’s phrenology all the way to Pierre Flourens’ holistic view. 

These turbulent debates were only dissipated thanks to the apparition of magnetic resonance imaging (MRI) used to non-invasively obtain structural images of the brain and functional MRI (fMRI). As neuronal activity triggers increased blood flow in the respective area, detecting the deoxygenated hemoglobin molecules (paramagnetic) gives insight into brain action. The resulting “Blood Oxygenation Level Dependent” (BOLD) signal depends on blood oxygenation, blood volume, and blood flow. Unfortunately, the raw information collected with fMRI is often not easily interpretable due to noise and other brain activity. However, the desired brain activity can be visualised by creating a model linking the input stimulus to the output fMRI data. By fitting the model to the raw data and plotting its weights onto a structural MRI image, it becomes apparent which voxels react strongly to the stimulus, effectively identifying the brain region responsible for a specific process. These technical advancements resulted in the general adoption of the distributed processing view of the brain, in which different areas are responsible for specific tasks, and complex processes result from the interactions between them. 

The complex function of interest in this project is the identification of faces. The core system responsible for facial recognition consists of three regions of the occipitotemporal visual extrastriate cortex. The first region is the inferior occipital gyrus and is associated with the perception of structural facial features. The second is the superior temporal sulcus and is related to changeable aspects of faces, such as perception of eye gaze and facial expressions. Finally, the third region is the lateral fusiform gyrus, which participates in identity recognition. In addition, the extended system includes brain regions that do not solely participate in facial recognition but aid the core system by extracting other meaningful information. One example is the amygdala, which, together with the insula, processes the emotional content of faces.

This project will try to understand how to use a general linear model (GLM) to extract information from brain signals. For simplification purposes, we will treat the data from a single voxel. 

---

# Methods

In order to acquire a detailed understanding of fMRI and the modeling of the resulting data, we will first build a fake raw fMRI signal and then decode it with a mathematical model.
We mimic showing participants images of faces, objects, or nothing with a series of rectangular pulses. The convolution of this input signal with the ideal Hemodynamic Response Function (HRF) gives us the ideal output data. A more realistic representation of this output is achieved by adding normally distributed noise to the HRF before convolution. Since fMRI data quality can easily be ruptured through a series of artefacts, we wanted to add some Gaussian noise to take into account a more genuine experimental design.

After applying a convolution between our HRF and stimulus signals, we then want to form a design matrix. This design matrix in the context of our problem will be separated into 4 separate columns. Those columns are: faces, objects, noise, and a constant column. The amount of columns we have will be the amount of predictors we will have when we fit our model. This step is important because the amount of predictors would widely affect the precision of fitting an oscillating signal.

After constructing the design matrix, a mathematical model is then fitted to the obtained imitation of raw fMRI data. The modelthat was alluded to was the General Linear Model (GLM), which calculates its weight (\\( \beta_{0}, \beta_{1}, ... \beta_{n} \\)) coefficients by the ordinary least squares (OLS) method, and was fitted with a mean square error cost function. We determine the quality of the fit by testing the optimal weights for statistical significance from the null hypothesis. Below we will display some of our simulations of these processes:

{% include figure image_path="images/projects/brain1/stim.png" alt="this is a placeholder image" caption="Our Brain Voxel Stimuli" %}

{% include figure image_path="images/projects/brain1/conv.png" alt="this is a placeholder image" caption="Visual Demonstration of Convolution" %}

{% include figure image_path="images/projects/brain1/stim2.png" alt="this is a placeholder image" caption="Our Brain Voxel Stimuli on more sporatic and instant signals"%}

{% include figure image_path="images/projects/brain1/conv2.png" alt="this is a placeholder image" caption="Visual Demonstration of Convolution of these sporatic signals" %}

As displayed above we can design a brain voxel experiment with any type of signal. We see that even if the stimuli are instant or are displayed for longer durations that our convolved signal takes a similar form. If we were to add more "rest time" between signals, we would see an oscillating sequence of the hrf function with respect to the amplitude of our signal. So really, we can fit any type of signal through these two steps which we then used as input. After doing so we can produce results of multiple different experiments by constructing the design matrix then fitting it into our GLM.

---

# Results

{% include figure image_path="images/projects/brain1/pred.png" alt="this is a placeholder image" caption="After fitting the GLM we can recover our convoluted Signal with accurate precision for a linear model (Square wave signals)" %}

{% include figure image_path="images/projects/brain1/pred2.png" alt="this is a placeholder image" caption="After fitting the GLM we can recover our convoluted Signal with accurate precision for a linear model (Sporatic Signals)" %}

Above we can see our predictions of our one voxel experimental design. The general linear model (GLM) applied to the signal was a good fit with a mean square error of 0.019 for the first experiment compared to the ideal expected output. Another behavior we quickly observed showed the effect of changing the \\( \alpha_{1} \\) and \\( \alpha_{2} \\) parameters in our HRF. A high \\( \alpha_{1} \\) value corresponds to lower amplitude, a slower rise time, and less undershoot. On the other hand, a high \\( \alpha_{2} \\) value results in an attenuated undershoot that more slowly returns to baseline. So by playing around with our alpha values, we could get some differentiating results. 

We also fitted our model onto real fMRI images. A one-voxel demonstration would not totally be sufficient to truly explain facial processing brain activity. Similar to our one-voxel signals, we take an fMRI recording that is presented with a series of stimulus events that could monitor brain activity. These images are then captured in the experiment and we could fit these signals (images) onto a GLM model. Using the FSLeyes Python Package which is widely used in Neural Processing, we apply a GLM fit to our data. However unlike our one-dimensional voxel we are able to locate spatially the actual brain activity. The big idea is if we apply OLS on each voxel of the brain, many of our predictors would remain constant in most regions of the brain. However at some important regions disclosed in our introduction like the occipitotemporal visual extrastriate cortex, we can see that those predictors increase or decrease significantly. By applying a mask to our array of predictors, we can also identify what signals are causing what regions to stimulate. We can then take our design matrix and map it to our brain regions that are being activated to see correspondence between the stimuli and the particular brain region. We display some of our results below:

{% include figure image_path="images/projects/brain1/stim3.png" alt="this is a placeholder image" caption="The stimuli of our real brain experiment" %}

{% include figure image_path="images/projects/brain1/brain.png" alt="this is a placeholder image" caption="The regions of the brain that were activated and to what extent through this particular experiment." %}



---

# Discussion

This project allowed us to gain insights into experimental design, linear modeling, and the hemodynamic response at the voxel & brain level. We learned that in order to validate our results, we would need to analyze the weights to determine if they are statistically different from the baseline, effectively informing us of their activation during facial recognition. We therefore performed some t-statistic tests: \\(t = \beta_{j} / \sigma_{j} \\), where \\(beta_{j} \\) refers to the estimated parameter for the regressor \\(j \\) and \\(sigma_j \\) refers to the standard error of regressor \\(j \\). We identified that t values that are more than two standard errors away from zero are statistically significant, and therefore we are more confident that the estimate is stable and not just an artefact of a small sample size. (*Our Statistics are displayed in our notebook*)

On top of that we concluded some other observations through this experimental design. Our first was that by varying the signal amplitude, one varies the signal-to-noise ratio (SNR), as most noise would remain constant. As a result, the model fit would suffer as the estimations would be more difficult due to a higher SNR. Also, noise is additive to the signal, so if we want to design a proper experiment, we should be at least of the same order of magnitude if we still want to extract meaningful information from it. Otherwise, the signals would be entirely be covered by the noise. 

Some concluding remarks is the amazing strengths of linear modeling. Our group was astonished to see how well we could predict voxel signals at such incredible precision. Additionally, by applying some high-level packages, we were able to apply this model onto actual fMRI data to gain meaningful information about the spatial locations of brain activity. With the brain being such a really complex structure, we were not surprised to see that multiple locations in the brain were actually activated when presented with particular stimuli. Therefore we come away from this project truly amazed at the power of simple computational algorithms in modeling brain activity. 

---

# Code
This project was done in NX-421 (Neural Signals & Signals Processing) at EPFL taught by Professor Dimitri Van De Ville as my mini project. Below I will list the source files that were made in this assignment as well as the code linked below it.

```mini_project_1.ipynb``` - the notebook that executes the stimulus recognition pipeline

```example_voxel_signal.npy``` - the numpy file containing an example voxel

{% include feature_row id="feature_row_left1" type="left" %}

---

# References

[1] Principles of Neural Science, Sixth Edition, 2021 - McGraw Hill. By Eric R. Kandel, John D. Koester, Sarah H. Mack and Steven A. Siegelbaum.

[2] Human Neural Systems for Face Recognition and Social Communication
James V. Haxby, Elizabeth A. Hoffman, and M. Ida Gobbini

[3] https://books.google.it/books?hl=en&lr=&id=G_qdEsDlkp0C&oi=fnd&pg=PA193&dq=experimental+design+number+trials+fMRI&ots=Xn2MByS6SG&sig=CNs2Qq6N0zj9DxKSuPwMnYpTH8c&redir_esc=y#v=onepage&q=experimental%20design%20number%20trials%20fMRI&f=false

---

# Collaborators

- Simon Lee 
- Julian Thomas Bär
- Veronika Calati
- Merkourios Simos
