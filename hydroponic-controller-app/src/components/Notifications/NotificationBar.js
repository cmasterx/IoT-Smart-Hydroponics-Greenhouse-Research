import React from 'react';
import './NotificationBar.css'
import NotificationIcon from './NotificationIcon'
import Clock from './Clock';
import '../../style.css'

// Notifications
import ArduinoState from './ArduinoState/ArduinoState'
import USBState from "./USBState/USBState";

class NotificationBar extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            notifications: {
                'arduino-state': React.createElement(ArduinoState)
            }
        }
    }

    componentDidMount() {
        window.setNavName = async (name) => {
            this.setState({ navname: name });
        };

        window.removeNavName = async (name) => {
            window.setNavName?.('');
        };
    }
    
    componentWillUnmount() {
        window.setNavName = undefined;
    }

    addNotification(id, element) {
        this.state.notifications[id] = element;
        this.setState({notifications: this.state.notifications});
    }
    
    updateNotification(id, element) {
        this.addNotification(id, element);
    }
    
    removeNotification(id) {
        delete this.state.notification[id];
        this.setState({notifications: this.state.notifications});
    }
    
    render() {
        const ifIcon = React.createElement(NotificationIcon, {disabled: true});
        
        var notifications = []
        for (var id in this.state.notifications) {
            notifications.push(this.state.notifications[id]);
        }
        
        return (
            <div className="NotificationBar">
                <Clock />
                {
                    notifications.map((notification, idx) => {
                        console.log('hello')
                    })
                }
                <ArduinoState />
                <USBState />
                <p>{this.state.navname}</p>
            </div>
        );
    }
}

export default NotificationBar;