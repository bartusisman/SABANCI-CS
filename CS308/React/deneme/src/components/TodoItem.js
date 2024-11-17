import React from 'react';
import './TodoItem.css';

function TodoItem({ todo, onDelete }) {
    return (
        <div className="todo-item">
            <span>{todo.text}</span>
            <button onClick={onDelete}>Delete</button>
        </div>
    );
}

export default TodoItem; 