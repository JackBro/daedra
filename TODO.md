**cloakd** *(kernel module)*

- [ ] Implement secure communication with userspace via *netlink* protocol
- [ ] Implement the following functionality:
  - [ ] hide/reveal itself
  - [ ] hide/reveal given pid


For inspiration see:
- [uzyszkodnik/rootkit](https://github.com/uzyszkodnik/rootkit)
- [silhouettes/rootkit](https://github.com/silhouettes/rootkit)
- [dgoulet/kjackal](https://github.com/dgoulet/kjackal)
- [phimuemue/rootkit-praktikum](https://github.com/phimuemue/rootkit-praktikum)
- [chokepoint/azazel](https://github.com/chokepoint/azazel)
- [nnewson/km](https://github.com/nnewson/km)
- [mfontanini/Programs-Scripts](https://github.com/mfontanini/Programs-Scripts/blob/master/rootkit/rootkit.c)
- [mncoppola/suterusu](https://github.com/mncoppola)

---
**Mephala** *(user-mode application)*

> The Prince of unknown plots and obfuscation, a master manipulator, a sewer of discord

*Mephala* is going to be designed around a POA (plugin-oriented architecture).

**config.xml**

```xml
<plugin name="plugin name" description="plugin description">

    <!-- 
        Load plugin automatically. Default value: no.
    -->
    <autostart value="yes"/>

    <!-- 
        If plugin terminates unexpectedly, we'll respawn it. Default value: no.
    -->
    <respawn value="yes"/>
    
    <!-- 
        This element governs plugin updates.
        If keep attribute is "yes", then we keep the old version, otherwise we remove the old version
        Default value is "no".
    -->
    <update url="https://some.url" keep="yes"/>
    
</plugin>
```

```lisp
(plugin 
    (name "plugin name") 
    (description "plugin description")
    
    ;Load plugin automatically. Default value: false
    (autostart #t)  
    
    ;If plugin terminates unexpectedly, we'll respawn it. Default value: false
    (respawn #t)    
    
    ;This symbol governs plugin updates.
    ;If keep attribute is true, then we keep the old version, otherwise we remove the old version
    ;Default value: false
    (update ((url "https://some.url") (keep #t)))
)
```
