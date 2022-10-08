---
title: "The Collatz Conjecture"
categories:
  - Blogging
tags:
  - Mathematics
  - Beauty
  - Mystery
---

Mathematics can most definitley be a head ache to many people including myself. However it is impossible to evade as almost every field of study uses mathematics as a stepping stone within their field. On the other hand, within mathematics is also a subfield of theorems, proofs, and conjectures that can be deemed as beautiful. Today I wanted to introduce a problem in mathematics with no intuition. Its been a problem that has long been worked on for many years, yet there is no feasible explanation for why this system occurs the way it does. It is called the **Collatz Conjecture**. 

The rules are fairly simple, pick any number \\(N\\) and apply these two simple rules. If positive (\\(N%2 == 0\\)) then you divide your current number by 2 (\\(N/2\\)) and if your number is odd (\\(N%2 == 1\\)) you multiply your current number by 3 and add 1 (\\(3N+1\\)). You would think that there would be a positive number that becomes infinite but this is not the case ever. Every single positive integer will end up in a 4-2-1 loop at some point and no one quite knows why? Here I have generated a plot that shows the iterations of the first 100,000 numbers on the number scale.

{% highlight Python linenos %}
def collatz(n):
    if n == 1:                             
        result = [1]
    elif n % 2 == 0:
        result = collatz(n // 2) + [n]
    elif n % 2 == 1:
        result = collatz((3 * n) + 1) + [n]
    return result

runs= N # pick a number here
seen = {}
sequence_lengths=[]
for i in tqdm.tqdm(range(1,runs)):
    length = collatz(i)
    plt.plot(length[::-1])
    sequence_lengths.append(len(length)) 
plt.title("First N integers within the collatz conjecture")
# plt.yscale('log') - if you want it in log-log scale
# plt.xscale('log') - if you want it in log-log scale
plt.xlabel("iterations")
plt.ylabel("number")
{% endhighlight %}

![image-center](/images/post_photos/3.png){: .align-center style="width: 60%;"}

In this graph no number surpasses 350 iterations and most numbers don't even surpass 250 iterations. If we view these numbers at a log-log scale which is *a scale on which the actual distance of a point from the scale's zero is proportional to the logarithm of the corresponding scale number rather than to the number itself* (merriam-webster.com), we see that all numbers have almost the same trend simply shifted along the x-axis which is so weird.  

![image-center](/images/post_photos/4.png){: .align-center style="width: 60%;"}
![image-center](/images/post_photos/5.png){: .align-center style="width: 60%;"}

To take it a step further mathematicians have made a new way to visualize this conjecture where you shift the number anti clockwise if its even and clockwise if it is odd. With that we get a beautiful portrayal of a feather like structure. This is where I was talking about how beauty is hidden in mathematics. 

![image-center](/images/post_photos/1.png){: .align-center style="width: 60%;"}

This problem has been impossible to prove and famous mathematician Paul Erdos says "Mathematics is not yet ripe enough for such questions". Therefore I have no inclination to speak any further. Hope you learned something and I hope you have a good day. 