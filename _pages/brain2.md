---
title: "Multivariate Stimulus Processing Across Brain Regions"
permalink: /projects/brain2/
layout: single
classes: wide
excerpt: "Modeling visual brain activity in multivariate approach"
header:
 overlay_image: images/projects/brain2/2.png
 caption: "Photo credit: Simon Lee"
date: 2022-12-01
sidebar:
  nav: "docs2"
feature_row_left1:
- url: "https://github.com/Simonlee711/EPFL/tree/main/NX-422/mini_projects/mini_project2"
  btn_label: "Code"
  btn_class: "btn--primary" 
---

# Keywords 

Independent Component Analysis, Multivariate Methods, Seed Connectivity, Functional Connectivity

---

# Introduction
Monitoring brain activity when presented with a stimulus allows us to distinguish areas of high activity. In a previous project, we looked at univariate approaches which perform the analysis at a per voxel basis. However, when generalized to all voxels they become computationally expensive and highly inefficient. Therefore the focus of this project is to take advantage of multivariate methods. In particular, independent component analysis (ICA) will help us investigate which parts of the brain are spatially active across subjects while watching a movie. We expect to see activation in the visual cortex, and in the default mode network (DMN) regions, which should be active during a resting state experiment. Moreover, we expect to visualize activity in the temporal lobes, caused by responses to sounds coming from the MRI apparatus.

---

# Methods
We used preprocessed fMRI data from 60 subjects watching a silent version of ‘Partly Cloudy’, a short animated video supposed to evoke emotional reactions. Functional data was collected with a gradient-echo EPI sequence sensitive to Blood Oxygen Level Dependent (BOLD) contrast in 32 near-axial slices covering the whole brain (EPI factor: 64; TE: 30 ms, flip angle: 90°).TR used was 2 s and the entire movie was 168 TRs (<6 min).

We ran ICA on this dataset. ICA is a popular multivariate approach in neuroscience, especially in fMRI, which restructures a multi-feature dataset via linear transformation into a self-organized set of functional networks. The advantage of this method over other eigendecomposition methods, like principal components analysis (PCA) or partial least squares correlation (PLSC), is that the components produced from the ICA are statistically independent in only one domain (spatial or temporal). Therefore, its strength lies in detecting brain responses while simultaneously denoising the data.

Two key criteria have to be met when using ICA. The first criterion is that the data must be statistically independent and that our data follows a non-Gaussian distribution. The goal ICA is to find a linear transformation of the feature space such that each of the individual new features is mutually independent:

\\[ X=[x_{1}, x_{2}...x_{i}]^{T}-> [y_{1}, y_{2},....,y_{i}]^{T}, where y_{i} \independent y_{j} \\]

To find this we can solve the following equation: \\(Y= WX + n \\) , where X is the original data, W is the weight matrix (linear transformation between X and Y), n  is noise and Y is the transformed data of independent components.This method can be justified by calculating mutual information, which is the measure of mutual dependence between two random variables (entropy - conditional entropy): 		


\\[ I(X ; Y) = H(X) - H(X|Y) \\]

This statistical test confirms that the new independent feature space \\((yi x yj)\\) has no mutual information, effectively justifying its independence: \\(I(yi ;yj)=0\\). Additionally, the mutual information of the new feature space (Y) with the original feature space (X) is the maximal sum of non-gaussianities of the estimates:  

\\[ I(Y ; X) = max. \\]

ICA was performed across 60 subjects. Adult (13) and child (47) data were analyzed both together and separately. We investigated three ICA cases with 5, 10, and 20 components respectively. We the performed seed functional connectivity using a brain map of 39 regions. We selected a voxel-seed within the primary visual cortex and a corresponding sphere-seed. Following that, we generated a 39-by-39 functional connectivity matrix, and we produced networks with varying connectivity thresholds, calculating the average local clustering coefficient (ALCC), and the local efficiency (LE).

---

# Results

{% include figure image_path="images/projects/brain2/6.png" alt="this is a placeholder image" caption="Frontal Lobe" %}
{% include figure image_path="images/projects/brain2/7.png" alt="this is a placeholder image" caption="Visual Cortex" %}

Multivariate Analysis - ICA:  In the case of 5-component ICA, individual regions in the brain could not be sufficiently distinguished. The two most meaningful components were the frontal lobe (Fig. 1.a) and the visual cortex (Fig. 1.b). In 10-component ICA, we were able to recognize a number of functional regions that were not present in the previous case, such as the temporal lobes (Fig. 2). 

{% include figure image_path="images/projects/brain2/8.png" alt="this is a placeholder image" caption="Temporal Lobe (Left Hemisphere)" %}
{% include figure image_path="images/projects/brain2/9.png" alt="this is a placeholder image" caption="Temporal Lobe (Right Hemisphere)" %}

We note that the right (Fig. 2.a) and left (Fig. 2.b) hemispheres were located in different individual components, which could point to preferential sampling of information, proposed by the ‘asymmetric sampling in time’ hypothesis. 

{% include figure image_path="images/projects/brain2/10.png" alt="this is a placeholder image" caption="" %}
{% include figure image_path="images/projects/brain2/11.png" alt="this is a placeholder image" caption="Noise Regions" %}

In 20-component ICA, most of the added components were nonspecific “noise” regions (Fig. 3), which did not contribute to our analysis. We also found very high similarity in the individual components of adults and children, indicating that the brain regions involved in the study are already well developed from a young age.

Considering the above findings, we can report three main active regions. The visual cortex, which is the primary site of visual information processing, was present in all ICA analyses. This is in line with our hypothesis and was expected, since the movie-watching task is highly visual. The second active region is the frontal lobe, which contains the prefrontal cortex and is the site where attention and memory are manifested. This is contradictory to our hypothesis, as it means that subjects were attentive and task-positive. It could also offer an explanation as to why the DMN was not present in any of the individual components. The third active region was the temporal lobes, associated with hearing. We must note here that, although some brain regions appear to have negative values, this does not mean that they are less active, but is a product of the mathematical analysis.

**Functional Connectivity:** We found that sphere-based seeding performed slightly better in producing high correlations with associated brain regions (Fig. 4). However, single-voxel seeding also produced meaningful correlations, and both methods were able to accurately demarcate the PVC (Fig. 5). The functional connectivity matrix (Fig. 6) is illustrated as a graph in Figure 7. The provided code also offers an interactive view of this graph. Networks with increasing connectivity thresholds and their ALCC and LE metrics are shown in Figure 8. We can observe that none of the networks are fully connected, and a correlation threshold above 0.6 essentially removes all edges.

{% include figure image_path="images/projects/brain2/4.png" alt="this is a placeholder image" caption="Sphere vs. Voxel based seeding" %}
{% include figure image_path="images/projects/brain2/5.png" alt="this is a placeholder image" caption="Highly Correlated Voxels (Sphere vs. Voxel)" %}
{% include figure image_path="images/projects/brain2/3.png" alt="this is a placeholder image" caption="Functional Connectivity Matrix" %}
{% include figure image_path="images/projects/brain2/2.png" alt="this is a placeholder image" caption="Functional Connectivity Network" %}
{% include figure image_path="images/projects/brain2/1.png" alt="this is a placeholder image" caption="Networks with different connectivity thresholds" %}

---

# Discussion - Theoretical Part
ICA is a powerful method, but one of its limitations is finding the correct number of components to obtain the clearest signals. In this project, multiple runs with different numbers of components were needed to get a set of meaningful results (Q1). 

The main motivation behind choosing ICA is its strength as a multivariate analysis tool that can work in resting-state conditions, while producing functionally interpretable results. In this case, GLM was ruled out, because it can only be applied to active-condition tasks that can produce meaningful regressors (Q2). 

ICA is agnostic to the number of components produced, which must be defined as a hyperparameter. Therefore, it is difficult to find an ideal number of components a priori, as was the case in our project. Even though some components have clear noise characteristics, they are spread out across multiple components and are difficult to confidently rule out. For this reason, other component analysis methods, such as PCA and PSLC, would be better suited for preprocessing GLM data (Q3).

A sphere seed (3D) can be a better alternative to voxel functional activity because it provides a better signal-to-noise ratio. Alternatively, one might use predefined brain atlases to perform functional connectivity, as in the connectivity matrix shown above (Q4). 

A graph representation of the brain offers many opportunities for quantitative analyses that wouldn’t be possible through simple contrast visualization. It is a powerful tool to investigate how different brain regions communicate, and it can offer important insights into the overarching architecture of the brain, such as whether the brain follows a centralized architecture, or whether it can be partitioned into distributed functional hubs (Q5).

---

## Footnotes

[1]  Vodrahalli, K., Chen, P.-H., Liang, Y., Baldassano, C., Chen, J., Yong, E., Honey, C., Hasson, U., Ramadge, P., Norman, K. A., & Arora, S. “Mapping between fMRI responses to movies and their natural language annotations” NeuroImage 2018 180:223–231

[2] Defining ICA by Mutual Information, http://cis.legacy.ics.tkk.fi/aapo/papers/IJCNN99_tutorialweb/node18.html

[3] Gael Varoquaux, Alexandre Gramfort, Fabian Pedregosa, Vincent Michel, and Bertrand Thirion. Multi-subject dictionary learning to segment an atlas of brain spontaneous activity. In Information Processing in Medical Imaging, 562–573. Berlin, Heidelberg, 2011. Springer Berlin Heidelberg.

[4] Poeppel D. “The analysis of speech in different temporal integration windows: cerebral lateralization as ‘asymmetric sampling in time’” Speech Communication 2003; 41:245-255

---

# Code

This project was done in NX-421 (Neural Signals & Signals Processing) at EPFL taught by Professor Dimitri Van De Ville as my mini project. Below I will list the source files that were made in this assignment as well as the code linked below it.

```ICA.ipynb``` - the notebook that executes the main pipeline

```New - Seed Functional Connectivity & Graph Metrics.ipynb``` - Extended analysis done for seed functional connectivity and graph based plots

{% include feature_row id="feature_row_left1" type="left" %}

---

# How to run code

There are two ways to run the program: (1) Jupyter Notebook 

1. Run the jupyter notebook

```
ICA.ipynb
```

```
New - Seed Functional Connectivity & Graph Metrics.ipynb
```

---

# Collaborators

- Simon Lee 
- Julian Thomas Bär
- Veronika Calati
- Merkourios Simos


