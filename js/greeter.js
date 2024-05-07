import next from 'next';

export function greet() {
    const s = next();
    if (s.length === 0) {
        return "JavaScript";
    }

    return `JavaScript and ${s}`;
}
