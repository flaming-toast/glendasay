glendasay
=========


          __
         (  \
     __   \  '\
    (  "-_ \ .-'----._          ___________________________    
     '-_  "v"         "-       /                           \ 
        "Y'             ".    |   A simple 9p fileserver   |
         |                |   |   reminiscent of cowsay.   |
         |        o     o |   /\___________________________/ 
         |          .<>.  |  /  
          \         "Ll"  |
           |             .'
           (             /
          /'\         . \
          "--^--.__,\_)-'

```sh
% ./glendasay -m /n/glendasay # default mountpoint
% echo hello world > /n/glendasay/ctl
. . . 
% fortune > /n/glendasay/ctl # redirect fortune's output 
. . .
```

TODO:
- Support longer text > 1 line (line wrap)
