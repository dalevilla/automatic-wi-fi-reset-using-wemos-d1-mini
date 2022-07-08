This device resets the Wi-Fi router when internet connection is lost. Due to frequent disconnection (usually 2 to 3 times a day), it causes frustration to the users because they have to manually reset the router everytime the connection is lost (connection does not return automatically). The manual reset is done by unplugging and plugging the adapter or pressing the router's power button two times. The user has no remote access for resetting the router since when the internet is lost, router log-ins does not work. This means that the user will have to walk to the router often, disrupting work flow. Even if the log-in method works, it is better to automate the process so the users does not have to reset it manually.

Basically, this device automates the process of manual resetting whenever the internet connection is lost.

# Materials

-Wemos D1 Mini
  The controls of the project. It is connected to the Wi-Fi, and upon disconnection, activates the normally closed relay to reset the router.
  
-5VDC Mechanical Relay
  Any 5VDC relay can be used as long as its contact capacity is rated for the voltage and current of the Wi-Fi router. In this case, the rating for the router is 12V 2A, so the relay used is SRD-05VDC-SL-C, which can handle up to 7A 28VDC. Also, this relay already has a flyback diode. 
  Note that 5VDC is highlighted since Wemos D1 Mini works on 5V logic, i.e., you’ll need to step-up or step-down the voltage output of Wemos if the relay works on higher or lower voltage level respectively. It is also important to use a DC relay because AC relays cannot handle long exposure to arcing. 

-5VDC Wall Adapter
  Micro USB to power the Wemos.
  
### Ma

Markdown is a lightweight and easy-to-use syntax for styling your writing. It includes conventions for

```markdown
Syntax highlighted code block

# Header 1
## Header 2
### Header 3

- Bulleted
- List

1. Numbered
2. List

**Bold** and _Italic_ and `Code` text

[Link](url) and ![Image](src)
```

For more details see [Basic writing and formatting syntax](https://docs.github.com/en/github/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax).

### Jekyll Themes

Your Pages site will use the layout and styles from the Jekyll theme you have selected in your [repository settings](https://github.com/dalevilla/automatic-wi-fi-reset-using-wemos-d1-mini/settings/pages). The name of this theme is saved in the Jekyll `_config.yml` configuration file.

### Support or Contact

Having trouble with Pages? Check out our [documentation](https://docs.github.com/categories/github-pages-basics/) or [contact support](https://support.github.com/contact) and we’ll help you sort it out.
