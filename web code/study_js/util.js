var EventUtil = {
    addHandler: function (element, type, handle) {
        if (element.addEventListener) {
            element.addEventListener(type, handle, false);
        } else if (element.attachEvent) {
            element.attachEvent("on" + type, handle);
        } else {
            element["on" + type] = handle;
        }
    },
    removeHandle: function (element, type, handle) {
        if (element.removeEventListener) {
            element.removeEventListener(type, handle, false);
        } else if (element.detachEvent) {
            element.detachEvent("on" + type, handle);
        } else {
            element["on" + type] = null;
        }
    },
    getRelatedTarget: function (event) {
        if (event.relatedTarget) {
            return event.relatedTarget;
        } else if (event.toElement) {
            return event.toElement;
        } else if (event.fromElement) {
            return event.fromElement;
        } return null;
    }

}