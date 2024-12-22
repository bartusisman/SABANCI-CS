/**
 * @class SceneNode
 * @desc A SceneNode is a node in the scene graph.
 *       It holds references to a MeshDrawer (for rendering), 
 *       a TRS (for transformations), and a list of children SceneNodes.
 */
class SceneNode {
    /**
     * @constructor
     * @param {MeshDrawer} meshDrawer - The MeshDrawer used for rendering
     * @param {TRS} trs - The TRS object for transformations
     * @param {SceneNode} [parent=null] - The parent SceneNode (if any)
     */
    constructor(meshDrawer, trs, parent = null) {
        this.meshDrawer = meshDrawer;
        this.trs = trs;
        this.parent = parent;
        this.children = [];

        // If there's a parent, automatically add this node to its children.
        if (parent) {
            this.parent.__addChild(this);
        }
    }

    /**
     * @private
     * @desc Internal method for adding a child to this SceneNode.
     *       (You do not usually call this directly; the constructor does it.)
     * @param {SceneNode} node - The child node
     */
    __addChild(node) {
        this.children.push(node);
    }

    /**
     * @desc Draw this node and all its children.
     * @param {Array} mvp - The current Model-View-Projection matrix
     * @param {Array} modelView - The current Model-View matrix
     * @param {Array} normalMatrix - The current Normal matrix
     * @param {Array} modelMatrix - The current Model matrix
     */
    draw(mvp, modelView, normalMatrix, modelMatrix) {
        // Start by assuming no changes to the incoming matrices
        let transformedMvp = mvp;
        let transformedModelView = modelView;
        let transformedNormals = normalMatrix;
        let transformedModel = modelMatrix;

        // If we have a TRS, apply its transformation
        if (this.trs) {
            let transformMatrix = this.trs.getTransformationMatrix();

            // Update matrices in the correct order (parent * local)
            transformedModel = MatrixMult(modelMatrix, transformMatrix);
            transformedModelView = MatrixMult(modelView, transformMatrix);
            transformedMvp = MatrixMult(mvp, transformMatrix);
            // For normal matrix, we'll just use the same transformation
            transformedNormals = MatrixMult(normalMatrix, transformMatrix);
        }

        // Draw the mesh, if available
        if (this.meshDrawer) {
            this.meshDrawer.draw(transformedMvp, transformedModelView, transformedNormals, transformedModel);
        }

        // Recursively draw children with the updated matrices
        for (let child of this.children) {
            child.draw(transformedMvp, transformedModelView, transformedNormals, transformedModel);
        }
    }
}
