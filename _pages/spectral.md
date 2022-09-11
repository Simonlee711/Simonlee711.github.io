---
title: "Spectral Analysis on Covid-19 Time Series"
permalink: /projects/spectral/
layout: single
classes: wide
excerpt: "A spectral viewpoint of the ongoing Covid-19 endemic argument"
header:
  overlay_image: /images/fft.png
  caption: "Spectral Analysis on Covid-19"
date: 2022-09-10
sidebar:
  nav: "docs2"
feature_row_left1:
  - url: "https://github.com/Simonlee711/Research/tree/master/Spectrum_Analysis/covidcase"
    btn_label: "Code"
    btn_class: "btn--primary"
---

# Abstract 

The Covid-19 pandemic has been a global issue for well over 2 years. However, recent reports suggests that it may be coming to an end with health officials claiming to treat it as a ``seasonal" endemic. Therefore to test the accuracy of these claims, our research runs time and spectral analysis on 8 countries Covid-19 time-series [data](https://github.com/datasets/covid-19/blob/main/data/time-series-19-covid-combined.csv). Our results reveal that the northern and southern hemisphere countries exhibit a series of outbreaks at the same time, strongly implying that there is no seasonal effect. In addition it also shows that outbreaks tend to occur bi-annually which also shows that it is very much still a pandemic. Therefore our data/analysis is potentially controversial as it disagrees with health officials and we strongly suggest it is premature to claim an end to this pandemic. 

---

# Keywords 

Spectral Analysis, Fast Fourier Transforms, Signals Processing, Covid-19 Time series analysis

---

# Introduction

As of today, the Covid-19 pandemic has stretched out for over two-plus years. And recently major news
outlets have made the bold claim that the Covid-19 “pandemic” is coming to an end. In December 2021
CDC director Rochelle Walensky said, “We have seen now that this is likely to become a seasonal endemic
disease here in the United States and really around the world” [1]. This news headline is among one of
many globally that are claiming an end to the pandemic and a start to an endemic. Many local governments
have since acted upon these claims by lifting mask mandates and returning to normalcy. However, we are
interested in challenging these claims to see if this is truly the direction in which this global pandemic is
trending. Luckily with the accumulation of 2 years of daily cases data, we can test these claims using tools
of mathematical analysis to assess our current status. So in this paper, we wish to explore the following
questions: Is there a seasonal trend in the COVID-19 pandemic? If so, can we call this a seasonal endemic
like the CDC suggests?

In order to answer this question we first must define what a “seasonal endemic” and “pandemic” is. In
the context of this paper we will define a seasonal endemic as a disease outbreak that occurs consistently in
a limited season. By contrast we will define a pandemic as a disease outbreak that is prevalent globally at
any time. So in order to arrive at an answer, we wish to explore the COVID-19 cases time series data of 8
countries (4 from the northern hemisphere & 4 from the southern hemisphere) and see whether there tends
to be “Covid spikes” in specific seasons. Through these Covid spikes we will determine from there whether
they satisfy the conditions of an endemic, or a pandemic. In order to collect our data, we plan on running
Fourier analysis to extract periodic trends and apply it with context to our time series data.

---

# Spectral Analysis

What is spectral analysis? In the simplest terms, it’s a method of observing spectra that appear within
frequencies. [2]. Especially when modeling pandemics, time-series data tends to show a periodic behavior.
For this reason our main objective is to get our data into spectra in order to measure the magnitude of an
input versus just a signal frequency. But first in order to do so, we must understand the difference between
the time and frequency domains. The time domain is typically some dynamical system that generates an
output within an evenly spaced amount of time. In terms of our data, we are specifically counting the weekly
cases that were recorded. Next, we have the frequency domain which is an analytical space in which “signals”
or “impulses” are conveyed in terms of frequencies.

The main advantage to observing our data in terms of the frequency domain is because Covid-19 data
contains noise. Noise is often associated with entropy or uncertainty and in short, it means there is some
corruption to the data [3]. Unfortunately, Covid-19 data is among some of the noisiest data and we need
a better way to see patterns within our time series data. So while we can observe Covid spikes in the time
domain, we may not truly understand the trends of Covid-19 in this general approach. Especially since
Covid cases are very subject to how much testing is done, whether the test is accurate (false positives, false
negatives), as well as how cases are not reported on weekends, we see our data fluctuate substantially from
week to week. Therefore using spectral analysis, we get the advantage of observing strong periodic impulses
that you cannot get from a time series approach. Hence, we can use this method to see whether there is a
seasonal effect with Covid-19.

---

# Mathematical Background

We now provide more detail into the methods by which we will obtain our results. In this subsection, we
will discuss Discrete Fourier Transforms (DFT), Fast Fourier Transforms (FFT), and the Power Spectrum
Density (PSD).

---

## Discrete Fourier Transform

The fundamental concept behind the Discrete Fourier Transforms is that it takes a data set instead of
a function like your typical Fourier Transform. Because we are working with a time series, all the numbers
are given whereas in a function, we have a determined values governed by the dependent variable. In a
Discrete Fourier transform, it takes a data set and transforms it into another data set that contains the
Fourier coefficients. The Fourier coefficients are computed in the following way:

\\[ X_k = X_0, X_1, X_1, X_2, ...... X_N, \\] 
\\[ X_k = \sum_{n=0}^{N-1} x_n e^{\frac{-2 \pi i (kn)}{N}} = \sum_{n=0}^{N-1} x_n [\cos(\frac{2 \pi kn}{N})-i \sin(\frac{2 \pi kn}{N})] \\]

where N is the total number of samples and n is the current sample. We also see the value k which is the
current frequency within the boundaries \\( k ∈ [0, N − 1] \\) and xn which is the value of the current sample.
With all those parts we compute the vector \\(X_{k}\\) which produces a complex number \\( (a + ib) \\) whose entries are
whats being shown in summation equation.

---

## Fast Fourier Transform

Now that we have laid out the mathematical foundation, we need to discuss how we get these results
numerically. To that, we introduce the Fast Fourier Transform (FFT) which is one the most prominent
algorithms that computes the DFT’s of any given time series data. This algorithm is a divide and conquer
algorithm, where it divides up the signal into smaller signals, computes the DFT of the smaller signals, and
joins them together. We therefore define \\(W\\) , as our complex number to simplify the the Discrete Fourier
transform equations:

\\[ W = e^{\frac{2 \pi i}{N}}. \\]

Doing so yields a similar equation like that of Discrete Fourier Transform. The Fast Fourier Transform can be seen as the following:

\\[ X_k = \sum_{n=0}^{N/2-1} W^{kn} x_n + \sum_{n=0}^{N/2-1} W^{kn} x_n. \\]

To compute the FFT, we would perform two separate matrix-vector products of the \\( x_{n} \\)’s vectors multiplied
to a matrix whose \\(k\\) and \\(n\\) elements is the the power to the W . This matrix vector product results into
another vector whose entries are the \\(X_{k} \\) values [9]. Danielson and Lanczos, created this numerical method
in which splitting up our DFT into two separate DFT’s \\( (N/2) \\)and summing them would produce the same
result compared to one giant DFT. This completely changes the time complexity of such computations where
a DFT is \\(O(n^{2})\\) while a FFT is \\(O(n log n)\\). This nearly linear time complexity was a breakthrough and this
algorithm is one of the most widely used and prominent algorithms of the 20th century

---

## Power Spectrum Density

Last of all, we want to talk about the Power Spectrum Density (PSD). A power spectrum \\(S_{xx}(f) \\) of a time
series \\(x(t) \\) describes the distribution of power into a frequency that shows up in the form of a signal/impulse.
[5] It is a popular method in Fourier analysis, and we can use it to see physical signals that are shot up over a
periodic range. The reason we care about the PSD is because it will reveal frequencies which have the largest
power to identify dominant periodic signals. Therefore in the context of our paper, we are looking to see
what periodic signals (spikes) we can see within a range of time (seasons). The following can be computed
with the below equation

\\[ \text{PSD} = (\frac{1}{\omega*\text{len(covid data)}}) * abs(\text{X})^2 . \\]

However, this still does not totally overcome our noise problem. In previous sections, we made an
emphasis on how noisy Covid-19 data was. Even when converting it to a frequency domain, some of this
noise is able to bypass the mitigation process and appear in our periodicity data. For this reason, many
impulses are actually shot up in our PSD. But what is misleading is that almost all these signals are very
minimal minus one or two impulses. So a popular trick in signal processing is to “denoise” our data by
setting some threshold that will drown out those tiny signals. Our decision to drown out these mini signals
was because by doing so we are killing the noise that may have gotten through [8]. This makes a more clear
and easier interpretation and it will be useful in analyzing the possible seasonal trends we might see in the
Covid-19 data.

---

# Data Availability

We obtained the Covid-19 time-series data from [John Hopkins University's Center for Systems Sciences and Engineering](https://github.com/datasets/covid-19/blob/main/data/time-series-19-covid-combined.csv). We used Covid cases data from March 5th, 2020 all the way up until February 7th, 2022. We used a start date of March 5th because most countries did not experience a patient zero until then. In order to see whether there is some endemic like behaviour, we must take into account the difference in seasons that occur naturally from the northern and southern hemispheres. Therefore we take a deeper look into 4 countries from each respective hemisphere: Argentina (Southern), Brazil (Southern), India (Northern), Indonesia (Southern), Russia (Northern), South Africa (Southern), United Kingdom (Northern), & The United States of America (Northern). The selection of these countries was motivated by mainly their population size as well as the countries that experienced the worst outbreaks during Covid. With our original hypothesis that winter is the worst  for infections, we want to see whether these claims are true within both hemispheres. 

---

# Methods

First, we took our daily cases time series and converted it into a weekly time series. We did this to mitigate some early noise within the data. Computationally we achieved this by writing a basic python script that would extract the data from the CSV files and store the dates as well as the case counts in separate lists. We repeated this process until we extracted all the daily case counts for each country. Next, we converted our daily case counts to weekly and we accomplished this by simply taking the summation of the case numbers and storing this into another list. We reset our summation every time our index hits a modulus of 7.

We then ran the Fast Fourier Transform (FFT) algorithm on our weekly time series data to get it into a frequency domain. We used the SciPy inbuilt FFT routine to extract the frequency power spectrum. Our python script as well as all our data is stored on Github and linked below the title. 

---

# Results & Discussion 

With all our data accumulated, we can truly address the question of whether there is a seasonal trend within the pandemic. With that, we actually disagree with the claim that this is an endemic at all. With the latest Omicron variant wave taking an extreme toll on cases worldwide, this shows that Covid-19 is a pandemic. Though some countries had some localized outbreaks that differed in periodicity in the case of Argentina \& India, we found that all the countries had no seasonal effect within our data. In many cases, countries experienced a peak at around 25 weeks, and in some cases we experienced peaks at 33 weeks. We were surprised by these results because if it were truly an endemic we would see a periodicity of around 52 weeks (1 year). 

In light of these results, we wanted to discuss some context to these periodic trends. The two most transmissible variants up to this point have been the delta (May 2021) and omicron variants (November 2022). They originated from India (delta), and South Africa (omicron), and we made an emphasis on studying these two countries for these reasons. At this point in the pandemic, there were no travel restrictions aside from Covid testing, and these variants had spread globally leading to the spikes seen around these times. Therefore, we know that if current trends continue based on the power spectra, we can be on the wrong side of the pandemic once more. Especially with the lifting of mask mandates across many counties, we believe this will yield another possible Covid outbreak in the months of June through August. Consequently by lifting restrictions, we believe that another variant can appear within the near future. 

{% include figure image_path="images/projects/vaccine.png" alt="this is a placeholder image" caption="Vaccine counts time series" %}

While we firmly believe that this is not an endemic, we would like to mention a caveat of our research. It is safe to say that there are definitely covariates within our data that are not considered. The major one is the protection we get from vaccines. Though we did not do any mathematics with the vaccination data, these are consideration we can make in future works. The effects of the vaccine are very substantial because they widely affect how we react to this virus. So in Figure 4 we see that a little less than half the population is still not vaccinated. This future research would require us to have daily vaccination time series which are very accessible from [Github](https://github.com/BloombergGraphics/covid-vaccine-tracker-data/tree/master/data). In addition we could see the vaccination counts with respect to the countries population to assess how lethal the virus is based off the rate of vaccinations. So knowing that a little under half the population remains unvaccinated, and that our research has assessed Covid-19 as a pandemic, we should keep a level of caution and not let our guard down for the time being.

---

# Concluding Remarks

With all that, we stand with the data that does not support classifying Covid-19 as a seasonal endemic. With our most recent outbreak being the worst one, we believe these new lackadaisical policies will lead to future outbreaks and continue to follow this pandemic like behavior. In the meantime, all we can really do is follow the World Health Organization (WHO) guidelines and keep up with the latest on new variants that may appear (i.e. BA.2 Omicron). Though we are all very much tired of the pandemic it is safe to say that it is not over and possibly will continue for an extended duration of time.

---

# Code

This project was done in AM 170A at UC Santa Cruz taught by Professor Pascale Gaurud. Below I will list the source files that were made in this assignment as well as the code linked below it.

```figures``` - folder where figures are saved

```north``` - folder of all of northern hemisphere data

```south``` - folder of all of southern hemisphere data

```Covid.ipynb``` - a jupyter notebook of analysis.py. Just easier to run

```analysis.py``` - generates all data for analysis

```time-series-19-covid-combined.csv``` - original file where data was scraped from

{% include feature_row id="feature_row_left1" type="left" %}

---

# How to run code

There are two ways to run the program: (1) Jupyter Notebook & (2) Unix based

1. Run the jupyter notebook

```
Covid.ipynb
```

2.Run the python file via Unix

```
python3 analysis.py
```
---

# References

[1] https://www.washingtonpost.com/wellness/2022/01/20/what-does-endemic-mean/

[2] http://web.stanford.edu/class/earthsys214/notes/series.htmlspectral-analysis

[3] https://www.techtarget.com/searchbusinessanalytics/definition/noisy-data

[4] Bochner, S.; Chandrasekharan, K. (1949), Fourier Transforms, Princeton University Press.

[5] P Stoica R Moses (2005). ”Spectral Analysis of Signals” (PDF).

[6] https://www.nytimes.com/live/2021/04/26/world/covid-vaccine-coronavirus-cases

[7] https://ourworldindata.org/covid-vaccinations?country=OWID WRL

[8] https://eeweb.engineering.nyu.edu/iselesni/DoubleSoftware/signal.html

[9] William H. Press ... [and others]. Numerical Recipes in C : the Art of Scientific Computing. Cambridge
[Cambridgeshire] ; New York :Cambridge University Press, 1992.