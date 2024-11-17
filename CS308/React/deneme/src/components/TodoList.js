import React, { useState } from 'react';
import TodoItem from './TodoItem';
import './TodoList.css';

function TodoList() {
    const [todos, setTodos] = useState([]);
    const [inputValue, setInputValue] = useState('');

    const addTodo = () => {
        if (inputValue.trim() !== '') {
            setTodos([...todos, { id: Date.now(), text: inputValue, completed: false }]);
            setInputValue('');
        }
    };

    return (
        <div className="todo-list">
            <h2>My Todo List</h2>
            <div className="todo-input">
                <input 
                    type="text" 
                    value={inputValue}
                    onChange={(e) => setInputValue(e.target.value)}
                    placeholder="Add a new todo"
                />
                <button onClick={addTodo}>Add</button>
            </div>
            <div className="todos">
                {todos.map(todo => (
                    <TodoItem 
                        key={todo.id} 
                        todo={todo} 
                        onDelete={() => setTodos(todos.filter(t => t.id !== todo.id))}
                    />
                ))}
            </div>
        </div>
    );
}

export default TodoList; 