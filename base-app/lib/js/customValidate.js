/*
 * =====================================================================================
 *
 *       Filename:  customValidate.js
 *
 *    Description:  A nice validate function that gives us better client side validation feedback
 *
 *        Version:  1.0
 *        Created:  01/10/11 08:36:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef CUSTOMVALIDATE_JS
#define CUSTOMVALIDATE_JS

/* Note: this is at the same time valid JavaScript and C++. */

WT_DECLARE_WT_MEMBER
(1, JavaScriptFunction, "validate",
    function (edit) {
        var v = edit.serverValidationResult; // Get the server result first
        if ((typeof v == "undefined") || (v.value != edit.value)) {
            // If there's no server result for this value, use the javascript validator
            v = edit.wtValidate.validate(edit.value);
        }
        var msgTxt = edit.msgTxt;
        if (v.valid) {
            edit.removeAttribute("title");
            $(edit).removeClass("Wt-invalid");
            if (typeof msgTxt !== "undefined") {
                $(msgTxt).text("");
            }
        } else {
            edit.setAttribute("title", v.message);
            $(edit).addClass("Wt-invalid");
            if (typeof msgTxt !== "undefined") {
                $(msgTxt).text(v.message);
            }
        }
    }
);

#endif // CUSTOMVALIDATE_JS
