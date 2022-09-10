---
title: "Fermi-Pasta-Ulam-Tsongui"
permalink: /fput/
layout: splash 
classes: wide
excerpt: "A unique Physics quasiliniear simulation"
header:
  overlay_image: /images/fput.jpg
  caption: "Photo credit: Simon Lee"
date: 2022-09-10

feature_row_left1:
  - url: "https://github.com/Simonlee711/CSE-13S/tree/master/asgn6"
    btn_label: "Code"
    btn_class: "btn--primary"
---

# Abstract

The Fermi-Pasta-Ulam-Tsingou problem in physics is an apparent paradox that given a system of point masses connected by springs, it will almost exactly form the same periodic behavior known as the Ferma-Pasta-Ulam-Tsingou recurrence, rather than an expected ergodic behaviour. This behaviour came by surprise because they expected the system to thermalize or reach thermal equilibrium in just a short amount of time. Yet the system appears to evade the ergodic hypothesis and this explanation remains a hot topic in research today. Therefore, in this project we are building a numerical analysis program that will help us visualize linear and nonlinear forms of the Fermi-Pasta-Ulam-Tsingou problem, to help us visualize this unique behaviour.

# History

In the summer of 1953 Enrico Fermi, John Pasta, Stanislaw Ulam, and Mary Tsingou conducted computer simulations of a vibrating string that included a non-linear term (quadratic in one test, cubic in another, and a piecewise linear approximation to a cubic in a third). They found that the behavior of the system was quite different from what intuition would have led them to expect. Fermi thought that after many iterations, the system would exhibit thermalization, an ergodic behavior in which the influence of the initial modes of vibration fade and the system becomes more or less random with all modes excited more or less equally. Instead, the system exhibited a very complicated quasi-periodic behavior. They published their results in a Los Alamos technical report in 1955. (Enrico Fermi died in 1954, and so this technical report was published after Fermi's death.)

# Governing Differential Equations

\\[\ddot{x} = f_{i} = K(x_{i+1}-2x_{i}+x_{i-1})(1+\alpha(x_{i+1}-x_{i-1}))\\
\\[x_{i}(0) = x_{i}^{0}\\]
\\[\dot{x} \_{i}(0) = v_{i}^{0}\\]



# Source Code

# How to run
