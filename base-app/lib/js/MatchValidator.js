/* Note: this is at the same time valid JavaScript and C++. */

WT_DECLARE_WT_MEMBER
(1, JavaScriptConstructor, "MatchValidator",
   function(mandatory, otherId, errorMsg) {
     this.validate = function(text) {
       var otherEle = document.getElementById(otherId);
       if (otherEle.tag == "input")
         var otherText = otherEle.getAttribute("value");
       else if (otherEle.tag == "textarea")
         var otherText = otherEle.getInnerHTML();
       if (text == otherText)
         return { valid: true };
       else
         return {
           valid: false,
           message: errorMsg
         };
     };
   });
