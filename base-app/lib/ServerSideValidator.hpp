/** Provides a server side validator.
  * Copyright Matthew D.G. Sherborne.
  * License GPL2 .. see LICENSE file.
  */
#ifndef SERVERSIDEVALIDATOR_HPP
#define SERVERSIDEVALIDATOR_HPP

#include <Wt/WValidator>
#include <Wt/WSignal>
#include <stdexcept>

using Wt::WValidator;
using Wt::Signal;

namespace wittyPlus {

/** The standard Wt::WValidator seems to make the assumption that nearly all validation that requires showing a message
  * will be done on the client side.
  * This class extends Wt::WValidator to provide a 'validateWithMessage' function on the server side.
  * It is intended to be used with validation that needs to be done server side, but where a message must be shown
  * to the client also. We don't show the message though, we just provide it in a signal when validate is called
  **/
class ServerSideValidator : public WValidator {
public:
    typedef Signal<State, WString> MsgSignal;
protected:
    WString _validMsg;
    WString _invalidMsg;
    MsgSignal _msgSignal; // This can be emited by descendant classes when we want to show a message
    /// Basically just emits the _msgSignal .. the app should hook into that to show stuff to the client,
    /// Possibly with a Wt::JSlot
    /// @param validationState the result of calling 'validate' function
    /// @param msg the message to show on the client side
    /// @return the validation result as a convenience
    State showMessage(State validationState, const WString& msg) const {
        _msgSignal.emit(validationState, msg);
        return validationState;
    }
    /// Shows the message to the client based on the validation result.
    /// @param validationState the result of calling 'validate' function
    /// @return the validation result as a convenience
    State showMessage(State validationState) const {
        showMessage(validationState, state2msg(validationState));
        return validationState;
    }
public:
    ServerSideValidator(
        const WString& validMsg="", const WString& invalidMsg="", const WString& emptyMsg="",
        bool isMandatory=false, WObject* parent=0)
        : WValidator(isMandatory, parent), _validMsg(validMsg), _invalidMsg(invalidMsg)
    {
        if (!emptyMsg.empty())
            setInvalidBlankText(emptyMsg);
    }
    ServerSideValidator(bool isMandatory, WObject* parent=0)
        : WValidator(isMandatory, parent), _validMsg(""), _invalidMsg("")
    {}
    /// Turns the output of Wt::WValidator::validate into a message for the end user
    WString state2msg(State validationResult) const {
        switch (validationResult) {
            case Valid: return _validMsg;
            case Invalid: return _invalidMsg;
            case InvalidEmpty: return invalidBlankText();
            default:
                throw std::logic_error("Did they add a new value to Wt::WValidator::State or something ?");
        }
    }
    // Accessors
    const WString& getValidMsg() { return _validMsg; }
    void setValidMsg(const WString& newMsg) { _validMsg = newMsg; }
    const WString& getInvalidMsg() { return _invalidMsg; }
    void setInvalidMsg(const WString& newMsg) { _invalidMsg = newMsg; }
    /// Descendants of this class can emit this signal. Users of the class can connect to it to push the message down
    /// to the client side.
    MsgSignal& msgSignal() { return _msgSignal; }
};

} // namespace wittyPlus
#endif // SERVERSIDEVALIDATOR_HPP
